import java.io.IOException;
import java.net.DatagramSocket;
import java.net.DatagramPacket;


public class ServerUDP {
    public static void main(String[] args) throws IOException {
        DatagramSocket serverSocket = new DatagramSocket(1234);

        while (true) {
            byte[] buffer = new byte[256];
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
            serverSocket.receive(packet);
            System.out.println("Received packet from " + packet.getAddress() + ":" + packet.getPort());
            String data =  new String(packet.getData(), 0, packet.getLength());

            String[] splitData = data.strip().split(" ");

            String operation;
            int number1;
            int number2;

            try {
                operation = splitData[0];
                number1 = Integer.parseInt(splitData[1]);
                number2 = Integer.parseInt(splitData[2]);
            } catch (Exception e) {
                serverSocket.send(createResponsePacket(
                        "Error occurred. Please provid the data like this: \"<add/subtract> <number1> <number2>\".",
                        packet
                ));
                continue;
            }

            int result;

            if (operation.equals("add")) {
                result = number1 + number2;
            } else if (operation.equals("subtract")) {
                result = number1 - number2;
            } else {
                serverSocket.send(createResponsePacket("Error in operation. Choose add or subtract.", packet));
                continue;
            }
            serverSocket.send(createResponsePacket("The answer is " + result + ".", packet));
        }
    }

    public static DatagramPacket createResponsePacket(String message, DatagramPacket packet) {
        byte[] messageBuffer = (message + "\n").getBytes();
        return new DatagramPacket(messageBuffer, messageBuffer.length, packet.getAddress(), packet.getPort());
    }
}
