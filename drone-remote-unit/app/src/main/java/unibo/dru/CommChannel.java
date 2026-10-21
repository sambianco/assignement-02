package unibo.dru;

public interface CommChannel {
    /**
     * Invia un messaggio testuale sulla linea seriale.
     */
    void sendMsg(String msg);

    /**
     * Preleva il prossimo messaggio ricevuto (bloccante se la coda è vuota).
     */
    String receiveMsg() throws InterruptedException;

    /**
     * Verifica se sono presenti messaggi ricevuti nella coda.
     */
    boolean isMsgAvailable();

    /**
     * Chiude la connessione seriale.
     */
    void close();
}
