/***************************************************************************
 *   Copyright (C) 2007 by Lothar May                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/* Session data (a session is a valid client connection). */

#ifndef _SESSIONDATA_H_
#define _SESSIONDATA_H_

#include <net/socket_helper.h>
#include <net/receivebuffer.h>
#include <string>
#include <boost/thread.hpp>

#define SESSION_ID_INIT			0

class SessionData
{
public:
	enum State { Init, ReceivingAvatar, Established, Game };

	SessionData(SOCKET sockfd, unsigned id);
	~SessionData();

	unsigned GetId() const;
	State GetState() const;
	void SetState(State state);

	SOCKET GetSocket() const;

	void SetReadyFlag();
	void ResetReadyFlag();
	bool IsReady() const;

	const std::string &GetClientAddr() const;
	void SetClientAddr(const std::string &addr);

	ReceiveBuffer &GetReceiveBuffer();

private:
	SOCKET							m_sockfd;
	const unsigned					m_id;
	State							m_state;
	std::string						m_clientAddr;
	ReceiveBuffer					m_receiveBuffer;
	bool							m_readyFlag;

	mutable boost::mutex			m_dataMutex;
};

#endif
