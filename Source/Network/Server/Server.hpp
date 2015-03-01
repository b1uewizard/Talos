// ========================================================================= //
// Talos - A 3D game engine with network multiplayer.
// Copyright(C) 2015 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
// File: Server.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// Defines Server class.
// ========================================================================= //

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

// ========================================================================= //

#include "stdafx.hpp"

// ========================================================================= //

class Entity;

// ========================================================================= //

namespace std{
    template<> 
    struct hash<RakNet::RakNetGUID>
    {
        size_t operator()(const RakNet::RakNetGUID& g) const
        {
            return hash<unsigned long>()(g.ToUint32(g));
        }
    };
}

// ========================================================================= //
// Operates network functionality for running a server with multiple clients.
class Server final
{
public:
    // Default initializes member data.
    explicit Server(void);

    // Empty destructor.
    ~Server(void);

    // Loads server settings from config file and sets up server connection.
    void init(const int port, const std::string& username);

    // Destroys server connection.
    void destroy(void);

    // Receives and handles incoming packets on server port.
    void update(void);

    // Getters:

    // Returns true if server has been initialized.
    const bool initialized(void) const;

    // === //

    struct Player{
        RakNet::RakString username;
        Entity* entity;
    };

private:
    // Processes new client registration.
    void registerNewClient(void);

    bool m_initialized;
    RakNet::RakPeerInterface* m_peer;
    RakNet::Packet* m_packet;
    unsigned int m_tickRate;  

    // Player instance of user running server.
    std::shared_ptr<Player> m_host;

    // Hash table of connected players.
    std::unordered_map<RakNet::RakNetGUID, std::shared_ptr<Player>> m_players;
};

// ========================================================================= //

inline const bool Server::initialized(void) const{
    return m_initialized;
}

// ========================================================================= //

#endif

// ========================================================================= //