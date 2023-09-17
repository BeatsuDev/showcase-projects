import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;


public class Server {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(1234);
        while (true) {
            Socket connection = acceptConnection(server);
            Thread clientThread = createClientThread(connection);
            clientThread.start();
        }
    }

    private static void serveClient(Socket socket) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);

        while (true) {
            // Ask the client for two numbers
            writer.println("Enter two numbers: ");
    
            // Read two numbers from the client and ask if the user wants to add or subtract them
            String line = reader.readLine();
            String[] numbers = line.split(" ");

            // Break if the client sent an empty line
            if (line.isEmpty()) {
                break;
            }
    
            // Check if the client input was valid
            if (numbers.length != 2 ) {
                writer.println("Invalid input. Enter two numbers separated by a space.");
                continue;
            }

            // Check if the arguments sent by the client are numbers
            try {
                Integer.parseInt(numbers[0]);
                Integer.parseInt(numbers[1]);
            } catch (NumberFormatException e) {
                writer.println("Invalid input. Enter two numbers separated by a space.");
                continue;
            }

            // Ask the client if they want to add or subtract the numbers
            writer.println("Enter 'add' or 'subtract': ");
            String operation = reader.readLine();

            // Check if the client input was valid
            if (!operation.equals("add") && !operation.equals("subtract")) {
                writer.println("Invalid input. Enter 'add' or 'subtract'.");
                continue;
            }

            // Perform the operation and send the result to the client
            int result = operation.equals("add") ? Integer.parseInt(numbers[0]) + Integer.parseInt(numbers[1]) : Integer.parseInt(numbers[0]) - Integer.parseInt(numbers[1]);
            writer.println("Result: " + result);
        }

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
