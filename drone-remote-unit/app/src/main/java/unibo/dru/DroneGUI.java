package unibo.dru;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class DroneGUI extends JFrame {

    private final CommChannel channel;

    // Etichette di monitoraggio
    private final JLabel lblDroneState = new JLabel("REST");
    private final JLabel lblHangarState = new JLabel("NORMAL");
    private final JLabel lblAltitude = new JLabel("--- cm");

    // Pulsanti di comando
    private final JButton btnTakeOff = new JButton("Take-Off");
    private final JButton btnLand = new JButton("Land");

    public DroneGUI(CommChannel channel) {
        super("Drone Remote Unit (DRU)");
        this.channel = channel;

        initUI();
        startReceiverLoop();
    }

    private void initUI() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(420, 320);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout(10, 10));

        // Pannello Centrale: Monitoraggio Telemetrico
        JPanel pnlTelemetry = new JPanel(new GridLayout(3, 2, 10, 10));
        pnlTelemetry.setBorder(BorderFactory.createTitledBorder("Stato di Sistema"));

        pnlTelemetry.add(new JLabel("Stato Drone:"));
        lblDroneState.setFont(new Font("SansSerif", Font.BOLD, 14));
        lblDroneState.setForeground(new Color(0, 102, 204));
        pnlTelemetry.add(lblDroneState);

        pnlTelemetry.add(new JLabel("Stato Hangar:"));
        lblHangarState.setFont(new Font("SansSerif", Font.BOLD, 14));
        lblHangarState.setForeground(new Color(0, 153, 76));
        pnlTelemetry.add(lblHangarState);

        pnlTelemetry.add(new JLabel("Quota (Suolo):"));
        lblAltitude.setFont(new Font("SansSerif", Font.BOLD, 14));
        pnlTelemetry.add(lblAltitude);

        add(pnlTelemetry, BorderLayout.CENTER);

        // Pannello Inferiore: Comandi di Volo
        JPanel pnlControls = new JPanel(new FlowLayout(FlowLayout.CENTER, 20, 10));
        btnTakeOff.setPreferredSize(new Dimension(140, 40));
        btnLand.setPreferredSize(new Dimension(140, 40));

        btnTakeOff.setEnabled(true);
        btnLand.setEnabled(false);

        // Azione Take-off
        btnTakeOff.addActionListener(e -> {
            channel.sendMsg("CMD:TAKEOFF");
            lblDroneState.setText("TAKING OFF");
            btnTakeOff.setEnabled(false);
            btnLand.setEnabled(true);
        });

        // Azione Land
        btnLand.addActionListener(e -> {
            channel.sendMsg("CMD:LAND");
            lblDroneState.setText("LANDING");
            btnLand.setEnabled(false);
        });

        pnlControls.add(btnTakeOff);
        pnlControls.add(btnLand);
        add(pnlControls, BorderLayout.SOUTH);
    }

    /**
     * Thread in background dedicato allo svuotamento della coda
     * e all'aggiornamento dell'interfaccia grafica tramite SwingUtilities.invokeLater.
     */
    private void startReceiverLoop() {
        new Thread(() -> {
            while (true) {
                try {
                    String msg = channel.receiveMsg();
                    SwingUtilities.invokeLater(() -> handleMessage(msg));
                } catch (InterruptedException ex) {
                    break;
                }
            }
        }).start();
    }

    private void handleMessage(String msg) {
        if (msg.startsWith("DIST:")) {
            String distVal = msg.substring(5).trim();
            lblAltitude.setText(distVal + " cm");
        } else if (msg.equals("ALARM")) {
            lblHangarState.setText("ALARM");
            lblHangarState.setForeground(Color.RED);
            JOptionPane.showMessageDialog(this, 
                "ALLARME TERMICO CRITICO RILEVATO DALL'HANGAR!", 
                "Emergenza Hangar", 
                JOptionPane.ERROR_MESSAGE);
        }
    }
}