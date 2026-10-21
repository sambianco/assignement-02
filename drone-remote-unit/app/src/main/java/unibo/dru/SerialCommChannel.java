package unibo.dru;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;

public class SerialCommChannel implements CommChannel, SerialPortEventListener {

    private final SerialPort serialPort;
    private final BlockingQueue<String> queue;
    private final StringBuffer currentMsg = new StringBuffer();

    public SerialCommChannel(String port, int rate) throws Exception {
        this.queue = new ArrayBlockingQueue<>(100);
        this.serialPort = new SerialPort(port);

        this.serialPort.openPort();
        this.serialPort.setParams(rate, 
                                  SerialPort.DATABITS_8, 
                                  SerialPort.STOPBITS_1, 
                                  SerialPort.PARITY_NONE);
        
        // Modalità non bloccante event-driven
        this.serialPort.setEventsMask(SerialPort.MASK_RXCHAR);
        this.serialPort.addEventListener(this);
    }

    @Override
    public void sendMsg(String msg) {
        char[] array = (msg + "\n").toCharArray();
        byte[] bytes = new byte[array.length];
        for (int i = 0; i < array.length; i++) {
            bytes[i] = (byte) array[i];
        }
        try {
            synchronized (serialPort) {
                serialPort.writeBytes(bytes);
            }
        } catch (Exception ex) {
            System.err.println("Errore invio seriale: " + ex.getMessage());
        }
    }

    @Override
    public String receiveMsg() throws InterruptedException {
        return queue.take();
    }

    @Override
    public boolean isMsgAvailable() {
        return !queue.isEmpty();
    }

    @Override
    public void close() {
        try {
            if (serialPort != null && serialPort.isOpened()) {
                serialPort.removeEventListener();
                serialPort.closePort();
            }
        } catch (Exception ex) {
            System.err.println("Errore chiusura porta: " + ex.getMessage());
        }
    }

    @Override
    public void serialEvent(SerialPortEvent event) {
        if (event.isRXCHAR()) {
            try {
                String msg = serialPort.readString(event.getEventValue());
                if (msg != null) {
                    for (int i = 0; i < msg.length(); i++) {
                        char ch = msg.charAt(i);
                        if (ch == '\n' || ch == '\r') {
                            String completeLine = currentMsg.toString().trim();
                            if (!completeLine.isEmpty()) {
                                queue.put(completeLine);
                                currentMsg.setLength(0);
                            }
                        } else {
                            currentMsg.append(ch);
                        }
                    }
                }
            } catch (Exception ex) {
                System.err.println("Errore ricezione seriale: " + ex.getMessage());
            }
        }
    }
}