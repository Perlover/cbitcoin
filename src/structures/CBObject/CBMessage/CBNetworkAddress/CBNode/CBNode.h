//
//  CBNode.h
//  cbitcoin
//
//  Created by Matthew Mitchell on 22/07/2012.
//  Copyright (c) 2012 Matthew Mitchell
//  
//  This file is part of cbitcoin.
//
//  cbitcoin is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  cbitcoin is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with cbitcoin.  If not, see <http://www.gnu.org/licenses/>.

/**
 @file
 @brief Contains data for managing node connections. "bytesTransferred/timeUsed" can be used to rank nodes for the most efficient ones which can be useful when selecting prefered nodes for download. Inherits CBNetworkAddress
*/

#ifndef CBNODEH
#define CBNODEH

//  Includes

#include "CBNetworkAddress.h"
#include "CBVersion.h"

/**
 @brief Structure for CBNode objects. @see CBNode.h
*/
typedef struct{
	CBNetworkAddress base; /**< CBNetworkAddress base structure */
	u_int64_t socketID; /**< Not used in the bitcoin protocol. This is used by cbitcoin to store a socket ID for a connection to a CBNetworkAddress. The socket here is not closed when the CBNetworkAddress is freed so needs to be closed elsewhere. */
	u_int64_t bytesTransferred; /**< Total bytes downloaded from the node. */
	u_int32_t timeUsed; /**< Total time taken to transfer the bytes to AND from the node. */
	u_int64_t receiveStart; /**< Time receiving has started */
	CBMessage * receive; /**< Receiving message. NULL if not receiving. This message is exclusive to the node. */
	CBMessage * sendQueue[CB_SEND_QUEUE_MAX_SIZE]; /**< Messages to send to this node. NULL if not sending anything. */
	u_int8_t sendQueueSize; /**< Upto 10 messages in queue */
	u_int8_t sendQueueFront; /**< Index of the front of the queue */
	u_int32_t messageSent; /**< Used by a CBNetworkCommunicator to store the message length send. When the header is sent, 24 bytes are taken off. */
	bool sentHeader; /**< True if the sending message's header has been sent. */
	u_int8_t * sendingHeader; /**< Stores header to send */
	bool getAddresses; /* True is asked for addresses, false otherwise. */
	u_int64_t receiveEvent; /**< Event for receving data from this node */
	u_int64_t sendEvent; /**< Event for sending data from this node */
	u_int64_t connectEvent; /**< Event for connecting to the node. */
	u_int16_t pingsSent; /**< Number of pings sent and thus how many responses expected */
	bool versionSent; /**< True if the version was sent to this node */
	CBVersion * versionMessage; /**< The version message from this node. */
	bool versionAck; /**< This node acknowledged the version message. */
	u_int8_t * headerBuffer; /**< Used by a CBNetworkCommunicator to read the message header before processing. */
	u_int32_t messageReceived; /**< Used by a CBNetworkCommunicator to store the message length received. When the header is received 24 bytes are taken off. */
	u_int16_t acceptedTypes; /**< Set messages that will be accepted on receiving. When a node tries to send another message, drop the node. Starts empty */
	bool receivedHeader; /**< True if the receiving message's header has been received. */
	int16_t timeOffset; /** The offset from the system time this node has */
	void * additionalData; /**< Extra pointer so the CBNetworkAddresses can be used to keep track of additional data. Not part of the bitcoin protocol. This is also not used in cbitcoin. */
} CBNode;

/**
 @brief Creates a new CBNode object.
 @returns A new CBNode object.
 */
CBNode * CBNewNodeByTakingNetworkAddress(CBNetworkAddress * addr);

/**
 @brief Gets a CBNode from another object. Use this to avoid casts.
 @param self The object to obtain the CBNode from.
 @returns The CBNode object.
 */
CBNode * CBGetNode(void * self);

/**
 @brief Initialises a CBNode object
 @param self The CBNode object to initialise
 @returns true on success, false on failure.
 */
bool CBInitNodeByTakingNetworkAddress(CBNode * self);

/**
 @brief Frees a CBNode object.
 @param self The CBNode object to free.
 */
void CBFreeNode(void * self);
 
//  Functions

#endif