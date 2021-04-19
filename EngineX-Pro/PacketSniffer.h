#pragma once
class PacketSniffer :public IAbstractModuleBase, public Singleton<PacketSniffer>
{
private:
	bool PacketSendIgnoreHeaders = false;
	bool PacketSendOnlyHeaders = false;
	bool PacketSendEnable = false;
	bool PacketSendReturnAddressEnable = false;


	bool PacketRecvIgnoreHeaders = false;
	bool PacketRecvOnlyHeaders = false;
	bool PacketRecvEnable = false;
	bool PacketRecvReturnAddressEnable = false;
	bool PacketSendRecvIgnoreHeaders = false;
	bool PacketSendRecvOnlyHeaders = false;
	bool PacketSendRecvEnable = false;

public:
	bool  IsEnablePacketSend()
	{
		return PacketSendEnable;
	}
	bool  IsEnablePacketRecv()
	{
		return PacketRecvEnable;
	}

	bool  IsEnableReturnAddressPacketSend()
	{
		return PacketSendReturnAddressEnable;
	}
	bool  IsEnableReturnAddressPacketRecv()
	{
		return PacketRecvReturnAddressEnable;
	}
	virtual void OnStart()
	{
	}

	virtual void OnStop()
	{
	}

	virtual void OnUpdate()
	{
	}

	virtual void OnRender()
	{
	}

	void OnTab1()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("SniffernBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Checkbox("Send Enable", &PacketSendEnable); ImGui::SameLine(); ImGui::Checkbox("Show Return Address", &PacketSendReturnAddressEnable);
		ImGui::Checkbox("Receive Enable", &PacketRecvEnable); ImGui::SameLine(); ImGui::Checkbox("Show Return Address", &PacketRecvReturnAddressEnable);
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(71, "PacketSniffer");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 71:
			OnTab1();
			break;
		}
	}
	
	void ProcessSendPacket(int len, void* pDestBuf, DWORD address)
	{
		BYTE header;
		memcpy(&header, pDestBuf, sizeof(header));
		BYTE* recvBuff = new BYTE[len];
		memcpy(recvBuff, pDestBuf, len);

		if (PacketSendEnable)
		{
			string headerName = sClientToServer[header];
			string packetHex = StringExtension::MakeHexString((BYTE*)pDestBuf, len, true, true);
			string ascii = StringExtension::BYTEToAsciiString(pDestBuf, len);
			
			string line = "[SEND][L:" + std::to_string(len) + "][" + headerName + "][" + packetHex + "]";
			Logger::AddString(Logger::SNIFFER, true, Logger::WHITE, line);
		
			Logger::AddString(Logger::SNIFFER, true, Logger::YELLOW, ascii);
			Logger::AddString(Logger::SNIFFER, true, Logger::YELLOW, StringExtension::DWORDToHexString(address));
		

		}
	}

	void ProcessRetPacket(int len, DWORD address)
	{
		if (PacketSendEnable)
		{
			Logger::AddString(Logger::SNIFFER, true, Logger::YELLOW, StringExtension::DWORDToHexString(address));


		}
	}

	void ProcessRecvPacket(int len, void* pDestBuf, DWORD address)
	{
		BYTE header;
		memcpy(&header, pDestBuf, sizeof(header));
		BYTE* recvBuff = new BYTE[len];
		memcpy(recvBuff, pDestBuf, len);

		if (header == 0x00)
		{
			return;
		}

		if (PacketRecvEnable)
		{
			string headerName = sServerToClient[header];
			string packetHex = StringExtension::MakeHexString((BYTE*)pDestBuf, len, true, true);
			string line = "[RECV][L:" + std::to_string(len) + "][" + headerName + "][" + packetHex + "]";
			string ascii = StringExtension::BYTEToAsciiString(pDestBuf, len);
			
			Logger::AddString(Logger::SNIFFER, true, Logger::WHITE, line);
			Logger::AddString(Logger::SNIFFER, true, Logger::YELLOW, ascii);

			Logger::AddString(Logger::SNIFFER, true, Logger::YELLOW, StringExtension::DWORDToHexString(address));
		}
	}

};




