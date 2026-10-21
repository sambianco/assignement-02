package unibo.dru;

import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;

import jssc.SerialPortList;

public class Main {
    public static void main(String[] args) {
        String[] portNames = SerialPortList.getPortNames();

        if (portNames.length == 0) {
            JOptionPane.showMessageDialog(null, 
                "Nessuna porta seriale trovata! Collega Arduino via USB.", 
                "Errore Seriale", 
                JOptionPane.ERROR_MESSAGE);
            return;
        }

        // Seleziona la porta (dialog se ce ne sono multiple)
        String selectedPort = portNames[0];
        if (portNames.length > 1) {
            selectedPort = (String) JOptionPane.showInputDialog(
                null, 
                "Seleziona la porta seriale di Arduino:", 
                "Scelta Porta", 
                JOptionPane.QUESTION_MESSAGE, 
                null, 
                portNames, 
                portNames[0]);
        }

        if (selectedPort == null) return;

        try {
            CommChannel channel = new SerialCommChannel(selectedPort, 9600);
            SwingUtilities.invokeLater(() -> {
                DroneGUI gui = new DroneGUI(channel);
                gui.setVisible(true);
            });
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null, 
                "Impossibile aprire la porta: " + ex.getMessage(), 
                "Errore Seriale", 
                JOptionPane.ERROR_MESSAGE);
        }
    }
}