import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;


public class WebServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(1234);
        while (true) {
            Socket connection = acceptConnection(server);
            Thread clientThread = createClientThread(connection);
            clientThread.start();
        }
    }

    private static void serveClient(Socket socket) throws IOException {
        PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);

        writer.println("HTTP/1.1 200 OK\r");
        writer.println("Content-Type: text/html; charset=utf-8\r");
        writer.println("");

        writer.println("<html><body><h1>Hei. Du har koblet deg opp til min enkle web-tjener.</h1></body></html>");

        try {
            socket.close();
        } catch (IOException e) {
            System.err.println("Error closing client connection.");
            System.exit(1);
        }
    }

    private static Socket acceptConnection(ServerSocket server) {
        try {
            return server.accept();
        } catch (IOException e) {
            System.err.println("Error accepting client connection.");
            return null;
        }
    }

    private static Thread createClientThread(Socket socket) {
        return new Thread(() -> {
            try {
                serveClient(socket);
            } catch (IOException e) {
                System.err.println("Error serving client: " + socket.getInetAddress() + ":" + socket.getPort());
            }
        });
    }
}
