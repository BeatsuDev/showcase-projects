# Connecting to TCP Server
You can use telnet for TCP connections.

`Server Terminal:`
    javac Server.java
    java Server

`Client Terminal:`
    telnet 127.0.0.1 1234

# Connecting to TCP WebServer
`Server Terminal:`
    javac WebServer.java
    java WebServer

Go to http://127.0.0.1:1234 in your web browser.

# Connecting to UDP Server
You can use netcat for UDP connections.

`Server Terminal:`
    javac ServerUDP.java
    java ServerUDP

`Client Terminal:`
    nc -u 127.0.0.1 1234

# Connecting to SSL Server
Run these commands before you run the server or client terminal:
Remember the password the you create in this step!

    keytool -genkey -alias signFiles -keyalg RSA -keystore examplestore

Replace <password> in the following commands with the password you created in the previous step:

`Server Terminal:`
    javac JavaSSLServer.java
    java -Djavax.net.ssl.keyStore=examplestore -Djavax.net.ssl.keyStorePassword=<password> JavaSSLServer

`Client Terminal:`
    javac JavaSSLClient.java
    java -Djavax.net.ssl.trustStore=examplestore -Djavax.net.ssl.trustStorePassword=<password> JavaSSLClient
