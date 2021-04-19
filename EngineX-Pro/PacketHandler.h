#pragma once


class PacketHandler
{
public:
	static bool AddressReceived;
	static bool Process();
	static bool SendHeartBeatResponse();
	static bool RecvHeartBeatPacket();
	static bool SendAuthPacket();
	static bool RecvAuthPacket();

protected:
	static bool CheckPacket(BYTE* header);
};
