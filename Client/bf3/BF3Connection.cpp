/*
 * Copyright (C) 2010 The OpenRcon Project.
 *
 * This file is part of OpenRcon.
 *
 * OpenRcon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenRcon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "BF3Connection.h"

BF3Connection::BF3Connection(QObject *parent) : Connection(parent)
{
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(tcpSocketReadyRead()));
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(tcpSocketStateChanged(QAbstractSocket::SocketState)));
}

BF3Connection::~BF3Connection()
{
    delete tcpSocket;
}

void BF3Connection::hostConnect(const QString &host, const int &port)
{
    // Check if tcpSocket is connected
    if (tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        qDebug() << "Connecting to BF3 server...";
        tcpSocket->connectToHost(host, port);
    } else {
        if (tcpSocket) {
            qDebug() << QString("Already connected to %1:%2").arg(tcpSocket->peerAddress().toString()).arg(tcpSocket->peerPort());
        } else {
            qDebug() << "ERROR: Connection::hostConnect() tcpSocket = 0";
        }
    }
}

bool BF3Connection::authenticated()
{
    return m_auth;
}

void BF3Connection::tcpSocketStateChanged(QAbstractSocket::SocketState state)
{
    qDebug() << QString("tcpSocket state changed: %1").arg(state);

    switch (state) {
        case QAbstractSocket::ConnectedState:
            qDebug() << "CONNECTED";
            m_auth = false; // Not authenticated yet
            //emit(startConnection());
            break;
        case QAbstractSocket::UnconnectedState:
            emit(logMessage("info", "Disconnected."));
            break;
        default:
            break;
    }
}

void BF3Connection::sendCommand(const QString &cmd)
{
    QTextStream out(tcpSocket);
    out << cmd + "\n";
}

void BF3Connection::authenticate()
{
    // Send login command
    if (digestSeedPassword.trimmed().length() > 0) {
        qDebug() << "Sending login... " + digestSeedPassword;
        sendCommand(QString("login %1").arg(digestSeedPassword));
    } else {
        qDebug() << "Digest seed password is missing. Connect again, please!!";
    }
}

void BF3Connection::tcpSocketReadyRead()
{
    QString receivedData;
    QString delimiterPattern1(":");
    QString delimiterPattern2(",");
    
    QStringList recvData;

    qDebug() << "BF3Connection::tcpSocketReadyRead()";
    QByteArray ba = tcpSocket->readAll();
	
    receivedData = QString(ba);
    
    // ONLY FOR TESTING PURPOSES
    QString players;
    players.append("Id:  1 -  halvors is remote ip: 84.49.231.146:62513 -> CD-key hash: e59dad54bf6e70efcdd69967d895a1f5");


    // Check if server is sending
    if (receivedData.trimmed().length() > 0) 
    {
        emit(logMessage("response", ba));
	
        // Use 'space' as separator for incomming data
        recvData = receivedData.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        
        // Check if Digest seed was sent by server
        // Split ':' character and select the first word ([0])
        if ((recvData.at(1) == "Digest") && (recvData.at(2).split(delimiterPattern1)[0] == "seed")) 
        {
            qDebug() << "Getting digest seed password...";
            // Encrypt password
            getDigestSeed(QString(ba));

            // Send encrypted password
            qDebug() << "Authenticating...";
            authenticate();
        } 
        // Split ',' character and select the first word ([0])
        else if ((recvData.at(0) == "Authentication") && 
                (recvData.at(1).split(delimiterPattern2)[0] == "successful")) 
        {
            qDebug() << "Authentication successful!!!: " + receivedData;
            qDebug() << "Requesting user list...";
            //sendCommand("exec admin.listPlayers");
            m_auth = true;
        } 
        // Receiving players list
        else if (recvData.at(0).split(delimiterPattern1)[0] == "Id")                  
        {
            // Split id and player name
            QString playerId = recvData.at(1);
            QString playerName = recvData.at(3).split(delimiterPattern1)[0];

          
    
            //qDebug() << "playerName: " << players[0].value("playerName");
            
        }
    } 
    else 
    {
        qDebug() << "Waiting data from server...";       
    }
	
	// FOR TESTING PURPOSES
	
    // Add id and player name to listPlayers
  
//    
//    PlayerItem pi;
//    pi.insertMulti("1", "usuario1");
//    pi.insertMulti("2", "loqueasea");
//    pi.insertMulti("3", "usuario1");
//    pi.insertMulti("4", "usuario3");
      
    playerList.insert("1", "usuario1");
    playerList.insert("2", "loqueasea");
    playerList.insert("3", "usuario1");
    playerList.insert("4", "usuario3");          

    QMap<QString, QString>::const_iterator i = playerList.constBegin();
            
    while (i != playerList.constEnd()) {
        qDebug() << "### Id: " << i.key() << " User name: " << i.value() << endl;
        ++i;
    }
    
//    players.push_back(pi);

    

}

const PlayerItem &BF3Connection::getPlayerList()
{
    return playerList;
}

void BF3Connection::getDigestSeed(const QString &data)
{
    QStringList md5string;

    QByteArray hash;
    QByteArray tmp;

    // Use space as separator
    md5string = data.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    // Used to check if digest string is found
    bool digestFound = false;

    // Used to check if seed value is found
    bool seedFound = false;

    digestFound = data.contains("Digest", Qt::CaseInsensitive);
    seedFound = data.contains("seed", Qt::CaseInsensitive);

    if (digestFound && seedFound) {
        digestSeedPassword = md5string.at(3) + "openrcon"; // TODO: Move this to BF3 and read current password
        tmp = digestSeedPassword.toLatin1();
        const char * tmpDigestSeedPassword = tmp.data();

        // Calculate md5 value for password (openrcon)
    	hash = QCryptographicHash::hash(tmpDigestSeedPassword, QCryptographicHash::Md5);		

        // Store digest seed password in hexadecimal value
        digestSeedPassword = QString(hash.toHex());

        qDebug() << "Encrypted password: " + digestSeedPassword;
    }
}
