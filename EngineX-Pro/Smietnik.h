#pragma once
//bool _fastcall Hooks::NewCEffectManagerRegisterEffect2(void* This, void* EDX, const char* c_szFileName, DWORD* pdwRetCRC, bool isNeedCache)
//{
//
//#if defined(PANGEA)
//	FishBot::ParseMessage(c_szFileName);
//
//#endif
//
//	return nCEffectManagerRegisterEffect2(This, c_szFileName, pdwRetCRC, isNeedCache);
//}



//##################################################################################################################################################
//static void FishingSielu(LPVOID line)
//{
//	DWORD time = GetTickCount();
//	vector<int> mili;
//	string str1 = (const char*)line;
//	string str2 = StringExtension::ReplaceString(str1, "LowienieRn ", "");
//
//	std::string delimiter = "|";
//
//	size_t pos = 0;
//	std::string token;
//	while ((pos = str2.find(delimiter)) != std::string::npos) {
//		token = str2.substr(0, pos);
//		mili.push_back(stoi(token));
//		str2.erase(0, pos + delimiter.length());
//	}
//	mili.push_back(stoi(str2));
//	int u[4];
//	u[0] = (mili[0]) * 9;
//	u[1] = (mili[1] - mili[0]) * 9;
//	u[2] = (mili[2] - mili[1])*9;
//	u[3] = (mili[3] - mili[2]) * 9;
//	for (int i = 0; i < 4; i++)
//	{
//		Sleep(u[i]);
//		GameFunctions::PythonPlayerNEW_Fishing();
//	}
//	string uu = "/fevent " + to_string((mili[0] + mili[1] + mili[2] + mili[3] )- 8);
//	Hooks::nCPythonNetworkStreamSendChatPacket((void*)Globals::iCPythonNetworkStreamInstance, uu.c_str(), 0);
//	Sleep(8000);
//
//	GameFunctions::NetworkStreamSendItemUsePacket(0);
//	GameFunctions::PythonPlayerNEW_Fishing();
//}


//#ifdef RUBINUM
//
//nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//#endif
//#ifdef AZENTIS
//
//
//
//
//
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//#endif
//#ifdef TAMIDIA_SE
//
//
//
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
////nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
//////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//#endif
//#ifdef AKADEMIA_NERWIA
//
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//#endif
//#ifdef NERWIAS2
//
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
////nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//#endif
//#ifdef SAMIAS2
//
//	/*nCPythonEventManagerRegisterEventSetFromString = (Globals::tCPythonEventManagerRegisterEventSetFromString)DetourFunction((PBYTE)Globals::CPythonEventManagerRegisterEventSetFromString, (PBYTE)NewCPythonEventManagerRegisterEventSetFromString);*/
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//#endif
//#ifdef BALMORA
//
//
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//#endif
//
//#ifdef ELENIUM
//
//
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//#endif
//
//#ifdef DIUMAR
//
//
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//#endif
//
//#ifdef TENELIS
//
//
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
///*nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);*/
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//#endif
//
//#ifdef MASTIAMT2
//
//
//
//
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//#endif
//
//#ifdef VIRTUALMT2
//
//nCNetworkStreamSendSequence = (Globals::tCNetworkStreamSendSequence)DetourFunction((PBYTE)Globals::CNetworkStreamSendSequence, (PBYTE)NewCNetworkStreamSendSequence);
///*//nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);*/
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
//#endif
//#ifdef HERMAS
//
//
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//
//
//#endif
//
//#ifdef ELITEMT2
///*nCEterPackManagerGet = (Globals::tCEterPackManagerGet)DetourFunction((PBYTE)Globals::CEterPackManagerGet, (PBYTE)HookCEterPackManagerGet);*/
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//#endif
//#ifdef LOTHIA
//
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//
//#endif
//#ifdef MULA
//Globals::CMappedFileSize = (Globals::tCMappedFileSize)(Globals::hEntryBaseAddress + 0x00233420);
//Globals::CEterPackManagerGet = (Globals::tCEterPackManagerGet)(Globals::hEntryBaseAddress + 0x0027ACB0);
//
//nCEterPackManagerGet = (Globals::tCEterPackManagerGet)DetourFunction((PBYTE)Globals::CEterPackManagerGet, (PBYTE)HookCEterPackManagerGet);
//#endif
//#ifdef VAROS
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//
//
//#endif
//#ifdef ALTRIC
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//
//
//#endif
//#ifdef VERESTHIA
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//
//
//#endif
//#ifdef AKADEMIA_VESTERIS
//
//	//nCEterFileDictInsertItem = (Globals::tCEterFileDictInsertItem)DetourFunction((PBYTE)Globals::CEterFileDictInsertItem, (PBYTE)NewCEterFileDictInsertItem);
//
//
//	//nCEterPackManagerGet = (Globals::tCEterPackManagerGet)DetourFunction((PBYTE)Globals::CEterPackManagerGet, (PBYTE)HookCEterPackManagerGet);
//
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//
//
//#endif
//#ifdef MEDIUM
//
//	//nCEterFileDictInsertItem = (Globals::tCEterFileDictInsertItem)DetourFunction((PBYTE)Globals::CEterFileDictInsertItem, (PBYTE)NewCEterFileDictInsertItem);
//	//nCEterPackManagerGet = (Globals::tCEterPackManagerGet)DetourFunction((PBYTE)Globals::CEterPackManagerGet, (PBYTE)HookCEterPackManagerGet);
//	//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
////nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
////nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
////nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
////nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
////nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
//////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//


//
//#endif
//#ifdef IVEYA
//
//
//nCPythonNetworkStreamSendChatPacket = (Globals::tCPythonNetworkStreamSendChatPacket)DetourFunction((PBYTE)Globals::CPythonNetworkStreamSendChatPacket, (PBYTE)NewCPythonNetworkStreamSendChatPacket);
///*nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);*/
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nPyCallClassMemberFunc2 = (Globals::tPyCallClassMemberFunc2)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc2, (PBYTE)NewPyCallClassMemberFunc2);
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//#endif



//#ifdef VALIUM

//DWORD pCResourceManagerGetResourcePointer = PatternScan::FindPattern("55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 83 EC 24 A1 ? ? ? ? 33 C5 89 45 F0 53 56 57 50 8D 45 F4 64 A3 ? ? ? ? 8B D9 8B 45 08");



//Globals::CResourceManagerGetResourcePointer = (Globals::tCResourceManagerGetResourcePointer)(pCResourceManagerGetResourcePointer);
//nCResourceManagerGetResourcePointer = (Globals::tCResourceManagerGetResourcePointer)DetourFunction((PBYTE)Globals::CResourceManagerGetResourcePointer, (PBYTE)NewCResourceManagerGetResourcePointer);


//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
////nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
////nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
////nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
////nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
////nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
////nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//
////nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
///*nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);*/
////nCActorInstance__CanPushDestActor = (Globals::tCActorInstance__CanPushDestActor)DetourFunction((PBYTE)Globals::CActorInstance__CanPushDestActor, (PBYTE)NewCActorInstance__CanPushDestActor);
//#endif
//#ifdef ESGAROTH
//
//
//	/*nCEterFileDictInsertItem = (Globals::tCEterFileDictInsertItem)DetourFunction((PBYTE)Globals::CEterFileDictInsertItem, (PBYTE)NewCEterFileDictInsertItem);*/
//
//
//	/*nCEterPackManagerGet = (Globals::tCEterPackManagerGet)DetourFunction((PBYTE)Globals::CEterPackManagerGet, (PBYTE)HookCEterPackManagerGet);*/
//nPyCallClassMemberFunc2 = (Globals::tPyCallClassMemberFunc2)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc2, (PBYTE)NewPyCallClassMemberFunc2);
//
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
//
//
//
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//
//
///*nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);*/
//#endif
//#ifdef ZAMORIA
//
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//#endif
//
//#ifdef ZERIOS
///*nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);*/
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//#endif
//#ifdef GLOBAL
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//#endif
//#ifdef GLADOR
////nCEterPackManagerGet = (Globals::tCEterPackManagerGet)DetourFunction((PBYTE)Globals::CEterPackManagerGet, (PBYTE)HookCEterPackManagerGet); //CItemManager::LoadItemList(%s) - StrangeLine in %d\n
////nCEterFileDictInsertItem = (Globals::tCEterFileDictInsertItem)DetourFunction((PBYTE)Globals::CEterFileDictInsertItem, (PBYTE)NewCEterFileDictInsertItem);//Pack index file size error! %s, indexCount %d
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nCResourceManagerGetResourcePointer = (Globals::tCResourceManagerGetResourcePointer)DetourFunction((PBYTE)Globals::CResourceManagerGetResourcePointer, (PBYTE)NewCResourceManagerGetResourcePointer);
////nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//nCNetworkStreamPeek = (Globals::tCNetworkStreamPeek)DetourFunction((PBYTE)(Globals::tCNetworkStreamPeek)(Globals::hEntryBaseAddress + 0x284290), (PBYTE)NewCNetworkStreamPeek);
////nCNetworkStreamCheckPacket = (Globals::tCNetworkStreamCheckPacket)DetourFunction((PBYTE)(Globals::tCNetworkStreamCheckPacket)(Globals::hEntryBaseAddress + 0x1E85A0), (PBYTE)NewCNetworkStreamCheckPacket);
////nCSnprintF = (Globals::tCSnprintF)DetourFunction((PBYTE)(Globals::tCSnprintF)(Globals::hEntryBaseAddress + 0x174640), (PBYTE)NewCSnPrintF);
////nCTerrainLoadMiniMapTexture = (Globals::tCTerrainLoadMiniMapTexture)DetourFunction((PBYTE)Globals::CTerrainLoadMiniMapTexture, (PBYTE)NewCTerrainLoadMiniMapTexture);
//#endif
//#ifdef PANGEA
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
///*Globals::CInstanceBaseRegisterEffect = (Globals::tCInstanceBaseRegisterEffect)(Globals::hEntryBaseAddress + 0xF9770);
//nCInstanceBaseRegisterEffect = (Globals::tCInstanceBaseRegisterEffect)DetourFunction((PBYTE)Globals::CInstanceBaseRegisterEffect, (PBYTE)NewCInstanceBaseRegisterEffect);*/
//DWORD pCEffectManagerRegisterEffect2 = PatternScan::FindPattern("55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 83 EC 1C A1 ? ? ? ? 33 C5 89 45 F0 53 56 57 50 8D 45 F4 64 A3 ? ? ? ? 8B D9 8B 7D 08");
//Globals::CEffectManagerRegisterEffect2 = (Globals::tCEffectManagerRegisterEffect2)(pCEffectManagerRegisterEffect2);
//nCEffectManagerRegisterEffect2 = (Globals::tCEffectManagerRegisterEffect2)DetourFunction((PBYTE)Globals::CEffectManagerRegisterEffect2, (PBYTE)NewCEffectManagerRegisterEffect2);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//#endif
//
//#ifdef XENOX
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//#endif
//#ifdef CLASSIC
//
//nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
////nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
////nCNetworkStreamSendSequence = (Globals::tCNetworkStreamSendSequence)DetourFunction((PBYTE)Globals::CNetworkStreamSendSequence, (PBYTE)NewCNetworkStreamSendSequence);
////nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
////nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
////nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
////nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
////nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nCSnprintF = (Globals::tCSnprintF)DetourFunction((PBYTE)(Globals::hEntryBaseAddress + 0x742D0), (PBYTE)NewCSnPrintF);
////nCPythonIsAtlas = (Globals::tCPythonIsAtlas)DetourFunction((PBYTE)Globals::CPythonIsAtlas, (PBYTE)NewCPythonIsAtlas);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//
////nCPythonItemCreateItem = (Globals::tCPythonItemCreateItem)DetourFunction((PBYTE)Globals::CPythonItemCreateItem, (PBYTE)NewCPythonItemCreateItem);
////nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
////nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
////nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//#endif
//#ifdef EGORIA
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
////nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
////nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
////nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
////nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
////nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
////nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//
////nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
///*nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);*/
//#endif
//
//#ifdef AVENTUS2
//nCNetworkStreamSendSequence = (Globals::tCNetworkStreamSendSequence)DetourFunction((PBYTE)Globals::CNetworkStreamSendSequence, (PBYTE)NewCNetworkStreamSendSequence);
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
///*//nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);*/
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//
//
//nCActorInstance__CanPushDestActor = (Globals::tCActorInstance__CanPushDestActor)DetourFunction((PBYTE)Globals::CActorInstance__CanPushDestActor, (PBYTE)NewCActorInstance__CanPushDestActor);
//#endif
//
//#ifdef SG2
////nCNetworkStreamSendSequence = (Globals::tCNetworkStreamSendSequence)DetourFunction((PBYTE)Globals::CNetworkStreamSendSequence, (PBYTE)NewCNetworkStreamSendSequence);
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
///*nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);*/
///*//nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);*/
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
////nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
////nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
//
//
//nCActorInstance__CanPushDestActor = (Globals::tCActorInstance__CanPushDestActor)DetourFunction((PBYTE)Globals::CActorInstance__CanPushDestActor, (PBYTE)NewCActorInstance__CanPushDestActor);
//#endif
//#ifdef MATADIA
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//#endif
//#ifdef VESTERIS
//
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
////nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
//
//
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
//#endif
//
//#ifdef BARIA
//nCPythonCharacterManagerDeform = (Globals::tCPythonCharacterManagerDeform)DetourFunction((PBYTE)Globals::CPythonCharacterManagerDeform, (PBYTE)NewCPythonCharacterManagerDeform);
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
////nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
//nCTerrainLoadMiniMapTexture = (Globals::tCTerrainLoadMiniMapTexture)DetourFunction((PBYTE)Globals::CTerrainLoadMiniMapTexture, (PBYTE)NewCTerrainLoadMiniMapTexture);
//#endif
//#ifdef ASGARDION
//
//#endif
//#ifdef MORAH
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
////nCRegisterInstance = (Globals::tCRegisterInstance)DetourFunction((PBYTE)Globals::CRegisterInstance, (PBYTE)NewCRegisterInstance);
////nCDeleteInstance = (Globals::tCDeleteInstance)DetourFunction((PBYTE)Globals::CDeleteInstance, (PBYTE)NewCDeleteInstance);
////nCDeleteInstanceByFade = (Globals::tCDeleteInstanceByFade)DetourFunction((PBYTE)Globals::CDeleteInstanceByFade, (PBYTE)NewCDeleteInstanceByFade);
//#endif
//#ifdef SENTHIA
//nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//
//#endif

//#ifdef ITANOS
//	nCPythonApplicationProcess = (Globals::tCPythonApplicationProcess)DetourFunction((PBYTE)Globals::CPythonApplicationProcess, (PBYTE)NewCPythonApplicationProcess);
//#endif
//
//void _fastcall Hooks::NewCGraphicTextInstanceSetValue(void* This, void* EDX, const char* c_szText, size_t len)
//{
//	if (strlen(c_szText) == 1)
//	{
//		DWORD base = Globals::hEntryBaseAddress;
//		DWORD back_address = (DWORD)_ReturnAddress() - base;
//		if (back_address == 0x001E79E3 || back_address == 0x0024427C)
//		{
//
//			FishBot::ParseMessage(c_szText);
//		}
//	}
//	return nCGraphicTextInstanceSetValue(This, c_szText, len);
//}

//this_thread::sleep_for(std::chrono::seconds(1));
	//MessageBox(NULL, L"BP", L"BreakePoint", 0);
	/*Globals::hWnds = Misc::GetToplevelWindows();
	TCHAR dllFilePath[512 + 1] = { 0 };
	TCHAR exeFilePath[512 + 1] = { 0 }; */
	//	GetModuleFileNameW(GetModuleHandle(NULL), exeFilePath, 512);
		//GetModuleFileNameW(Globals::hModule, dllFilePath, 512);
		//string dllDirPathStr = FileExtension::GetDirectoryPathFromFilePatch(StringExtension::StringFromWChar(dllFilePath));	
		//MessageBox(NULL, dllFilePath, L"Path", NULL);
		//Globals::dllDirPath = dllDirPathStr.c_str();
		//MemoryExtension::ErasePEHeader(Globals::hModule);

/*AllocConsole();
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);*/



//		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//#if defined (NEED_LICENSE)
//bool  MainCore::LoadLicense(const char* dirPath)
//{
//	LicenseInformation licenseInformation;
//	memset(&licenseInformation, 0, sizeof(licenseInformation));
//	vector<char> i = FileExtension::ReadAllBYTEs(dirPath);
//
//	Xor32::Decrypt((unsigned char*)&i[0], 0, i.size());
//
//
//
//	memcpy(&licenseInformation, &i[0], sizeof(LicenseInformation));
//	if (strcmp(licenseInformation.getHWID, ProtectExtension::GetHWID().c_str()) == 0)
//	{
//		/*MessageBox(NULL, L"Licencja Ok", L"Info", NULL);*/
//		Globals::licenseInformation = licenseInformation;
//	}
//	else
//	{
//		MessageBox(NULL, L"Maszyna-Brak Licencji", L"Error", NULL);
//		exit(0);
//	}
//	if (!StringExtension::Equals(licenseInformation.serverName, SERVER_NAME))
//	{
//		MessageBox(NULL, L"Serwer-Brak Licencji", L"Error", NULL);
//		exit(0);
//	}
//
//	SYSTEMTIME systemTime = Misc::GetServerTime();
//
//	if (systemTime.wYear == 0 || systemTime.wMonth == 0)
//	{
//		MessageBox(NULL, L"Error Number #12", L"Error", NULL);
//		exit(0);
//	}
//	std::tm tm1 = { 0 };
//	tm1.tm_year = systemTime.wYear - 1900;
//	tm1.tm_mon = systemTime.wMonth - 1;
//	tm1.tm_mday = systemTime.wDay;
//
//
//
//
//
//	std::tm tm2 = { 0 };
//	tm2.tm_year = (Globals::licenseInformation.createYear + 2000) - 1900;
//	tm2.tm_mon = Globals::licenseInformation.createMonth - 1;
//	tm2.tm_mday = Globals::licenseInformation.createDay;
//
//	std::time_t time1 = std::mktime(&tm1);
//	std::time_t time2 = std::mktime(&tm2);
//
//
//	const int seconds_per_day = 60 * 60 * 24;
//	std::time_t difference = (time1 - time2) / seconds_per_day;
//	std::time_t difference2 = (time2 - time1) / seconds_per_day;
//
//
//
//
//
//
//
//	if (difference > Globals::licenseInformation.daysLimit)
//	{
//		MessageBox(NULL, L"Licencja Wygasła", L"Error", NULL);
//		exit(0);
//	}
//	else
//	{
//		DWORD left = -1;
//		if (difference < Globals::licenseInformation.daysLimit)
//		{
//			left = (Globals::licenseInformation.daysLimit - difference);
//		}
//		else
//		{
//			left = (difference - Globals::licenseInformation.daysLimit);
//		}
//		Globals::licenseDayLeft = left;
//
//	}
//
//
//	return true;
//}
//#endif
//
//void MainCore::Test()
//{
//
//
//}

//
//#ifdef HERMAS
//	typedef void(__thiscall* tCPythonPlayerPickCloseItem)(void* This, bool a2);
//#else
//
//#endif
//
//typedef DWORD(__thiscall* tCPythonNetworkStreamGetMainActorVID)(void* This);
//
//typedef void(__thiscall* tCPythonPlayerPickCloseItem)(void* This);
//typedef bool(__thiscall* tCInstanceBaseIsWaiting)(void* This);
//
//typedef bool(__thiscall* tCPythonItemGetPickedItemID)(void* This, DWORD* pdwPickedItemID);
//typedef float(__thiscall* tCInstanceBaseGetDistance)(void* This, DWORD* pkTargetInst);
//typedef void(__thiscall* tCPythonPlayerSetStatus)(void* This, DWORD dwType, long lValue);
//typedef bool(__thiscall* tCInstanceBaseCheckAdvancing)(void* This);
//
//typedef void(__thiscall* tCInstanceBaseSetMoveSpeed)(void* This, UINT uMovSpd);
//typedef void(__thiscall* tCInstanceBaseSetAttackSpeed)(void* This, UINT uAtkSpd);
//typedef DWORD* (__thiscall* tCRegisterInstance)(void* This, DWORD vid);
//typedef void(__thiscall* tCDeleteInstance)(void* This, DWORD vid);
//typedef void(__thiscall* tCDeleteInstanceByFade)(void* This, DWORD vid);
//typedef bool(__thiscall* tCPythonIsAtlas)(void* This);
//
//typedef	int(__cdecl* tCSnprintF)(char* a1, size_t a2, const char* a3, ...);
//typedef bool(__thiscall* tCPythonCharacterManagerIsDeadVID)(void* This, DWORD dwVID);
//

/*typedef void(__thiscall* tCInstanceBaseRenderCollision)(void* This);*/
	/*typedef void(__thiscall* tCScreenRenderCircle3D)(void* This,float fx, float fy, float fz, float fRadius, int iStep);
	typedef void(__thiscall* tCGetBoundingSphere)(void* This, D3DXVECTOR3& v3Center, float& fRadius);
	typedef void(__thiscall* tCScreenRenderSphere)(void* This, const D3DXMATRIX* c_pmatWorld, float fx, float fy, float fz, float fRadius, D3DFILLMODE d3dFillMode);
	typedef void(__thiscall* tCPythonCharacterManagerDeform)(void* This);
	typedef void(__thiscall* tCInstanceBaseSetAddColor)(void* This, const D3DXCOLOR& color);
	typedef void(__thiscall* tCInstanceBaseSetAddRenderMode)(void* This);
	typedef void(__thiscall* tCInstanceBaseRestoreRenderMode)(void* This);*/



//
//
//
////#################################################################################################################################
//static void GetBoundingSphere(DWORD* instance, D3DXVECTOR3& v3Center, float& fRadius)
//{
//	return Globals::CGetBoundingSphere((void*)instance, v3Center, fRadius);
//}
////#################################################################################################################################
//static void RenderSphere(const D3DXMATRIX* c_pmatWorld, float fx, float fy, float fz, float fRadius, D3DFILLMODE d3dFillMode)
//{
//	return Globals::CScreenRenderSphere((void*)Globals::iCScreenInstance, c_pmatWorld, fx, fy, fz, fRadius, d3dFillMode);
//}
////#################################################################################################################################
//static void InstanceBaseSetAddColor(DWORD* instance, const D3DXCOLOR& color)
//{
//	return Globals::CInstanceBaseSetAddColor((void*)instance, color);
//}
////#################################################################################################################################
//static void InstanceBaseSetAddRenderMode(DWORD* instance)
//{
//	return Globals::CInstanceBaseSetAddRenderMode((void*)instance);
//}
////#################################################################################################################################
//static void InstanceBaseRestoreRenderMode(DWORD* instance)
//{
//	return Globals::CInstanceBaseRestoreRenderMode((void*)instance);
//}
////#################################################################################################################################
//
//static void RecvCaptcha()
//{
//	return Globals::CRecvCaptcha((void*)Globals::iCPythonNetworkStreamInstance);
//}
//
//static void* MappedFileConstructor(void* ins)
//{
//	return Globals::CMappedFileConstructor(ins);
//}
//
////#################################################################################################################################
//static void ProjectPosition(float fx, float fy, float fz, float* ex, float* ey, float* ez)
//{
//	return Globals::CScreenProjectPosition((void*)Globals::iCScreenInstance, fx, fy, fz, ex, ey, ez);
//}
////#################################################################################################################################
//static void RenderCircle3D(float fx, float fy, float fz, float fRadius, int iStep)
//{
//	return Globals::CScreenRenderCircle3D((void*)Globals::iCScreenInstance, fx, fy, fz, fRadius, iStep);
//}
//static bool InstanceBaseIsWaiting(DWORD* instance)
//{
//	return Globals::CInstanceBaseIsWaiting(instance);
//}
//
////#################################################################################################################################
//static bool CharacterManagerIsDeadVID(DWORD dwVID)
//{
//	return Globals::CPythonCharacterManagerIsDeadVID((void*)Globals::iCPythonCharacterManagerInstance, dwVID);
//}
//
////#################################################################################################################################
//static void InstanceBaseSetMoveSpeed(DWORD* instance, int value)
//{
//	return Globals::CInstanceBaseSetMoveSpeed(instance, value);
//}
////#################################################################################################################################
//static void InstanceBaseSetAttackSpeed(DWORD* instance, int value)
//{
//	return Globals::CInstanceBaseSetAttackSpeed(instance, value);
//}
//
////#################################################################################################################################
//static void PlayerPickCloseItem()
//{
//#ifdef HERMAS
//	Globals::CPythonPlayerPickCloseItem((void*)Globals::iCPythonPlayerInstance, false);
//#else
//	Globals::CPythonPlayerPickCloseItem((void*)Globals::iCPythonPlayerInstance);
//#endif
//}
//static tCInstanceBaseRenderCollision CInstanceBaseRenderCollision;
/*static tCScreenRenderCircle3D CScreenRenderCircle3D;*/
/*static tCActorInstanceGetPixelPosition CActorInstanceGetPixelPosition;
	static tCGetBoundingSphere CGetBoundingSphere;
	static tCScreenRenderSphere CScreenRenderSphere;
	static tCPythonCharacterManagerDeform CPythonCharacterManagerDeform;
	static tCInstanceBaseSetAddColor CInstanceBaseSetAddColor;
	static tCInstanceBaseSetAddRenderMode CInstanceBaseSetAddRenderMode;
	static tCInstanceBaseRestoreRenderMode CInstanceBaseRestoreRenderMode;
	static tCRecvCaptcha CRecvCaptcha;*/
	/*static tGlobals::tCInstanceBaseRenderCollision Globals::CInstanceBaseRenderCollision = NULL;
//Globals::tCScreenRenderCircle3D Globals::CScreenRenderCircle3D = NULL;
//Globals::tCActorInstanceGetPixelPosition Globals::CActorInstanceGetPixelPosition = NULL;
//Globals::tCGetBoundingSphere Globals::CGetBoundingSphere = NULL;
//Globals::tCScreenRenderSphere Globals::CScreenRenderSphere = NULL;
//Globals::tCPythonCharacterManagerDeform Globals::CPythonCharacterManagerDeform = NULL;
//Globals::tCInstanceBaseSetAddColor Globals::CInstanceBaseSetAddColor = NULL;
//Globals::tCInstanceBaseSetAddRenderMode Globals::CInstanceBaseSetAddRenderMode = NULL;
//Globals::tCInstanceBaseRestoreRenderMode Globals::CInstanceBaseRestoreRenderMode = NULL;
//Globals::tCRecvCaptcha Globals::CRecvCaptcha = NULL;
Globals::tCMappedFileConstructor Globals::CMappedFileConstructor = NULL;
if (pCInstanceBaseRenderCollision != NULL) {
		CInstanceBaseRenderCollision = (tCInstanceBaseRenderCollision)(pCInstanceBaseRenderCollision);
	}
/*if (pCScreenRenderCircle3D != NULL) {
		CScreenRenderCircle3D = (tCScreenRenderCircle3D)(pCScreenRenderCircle3D);
	}*/


	/*if (pCActorInstanceGetPixelPosition != NULL) {
			CActorInstanceGetPixelPosition = (tCActorInstanceGetPixelPosition)(pCActorInstanceGetPixelPosition);
		}
		if (pCGetBoundingSphere != NULL) {
			CGetBoundingSphere = (tCGetBoundingSphere)(pCGetBoundingSphere);
		}
		if (pCScreenRenderSphere != NULL) {
			CScreenRenderSphere = (tCScreenRenderSphere)(pCScreenRenderSphere);
		}
		if (pCPythonCharacterManagerDeform != NULL) {
			CPythonCharacterManagerDeform = (tCPythonCharacterManagerDeform)(pCPythonCharacterManagerDeform);
		}
		if (pCInstanceBaseSetAddColor != NULL) {
			CInstanceBaseSetAddColor = (tCInstanceBaseSetAddColor)(pCInstanceBaseSetAddColor);
		}*/
		/*if (pCInstanceBaseSetAddRenderMode != NULL) {
			CInstanceBaseSetAddRenderMode = (tCInstanceBaseSetAddRenderMode)(pCInstanceBaseSetAddRenderMode);
		}*/
		/*if (pCInstanceBaseRestoreRenderMode != NULL) {
			CInstanceBaseRestoreRenderMode = (tCInstanceBaseRestoreRenderMode)(pCInstanceBaseRestoreRenderMode);
		}*/
		/*if (pCRecvCaptcha != NULL) {
			CRecvCaptcha = (tCRecvCaptcha)(pCRecvCaptcha);
		}*/
		/*if (pCPythonIsAtlas != NULL) {
			CPythonIsAtlas = (tCPythonIsAtlas)(pCPythonIsAtlas);
		}*/
		/*if (pCMappedFileConstructor != NULL) {
				CMappedFileConstructor = (tCMappedFileConstructor)(pCMappedFileConstructor);
			}*/

			/*if (pCInstanceBaseIsWaiting != NULL)
				{
					CInstanceBaseIsWaiting = (tCInstanceBaseIsWaiting)(pCInstanceBaseIsWaiting);
				}*/

				/*if (pCPythonCharacterManagerIsDeadVID != NULL)
					{
						CPythonCharacterManagerIsDeadVID = (tCPythonCharacterManagerIsDeadVID)(pCPythonCharacterManagerIsDeadVID);
					}*/


//static void InstanceBaseRenderCollision(DWORD* instance)
//{
//	return Globals::CInstanceBaseRenderCollision((void*)instance);
//}

//##################################################################################################
//bool _fastcall Hooks::NewCInstanceBaseCheckAdvancing(void* This, void* EDX)
//{
//	if (Settings::MiniMHWALL)
//	{
//		return true;
//	}
//	else
//	{
//		return nCInstanceBaseCheckAdvancing(This);
//	}
//}

//
//typedef void(__thiscall* tCScreenProjectPosition)(void* This, float x, float y, float z, float* pfX, float* pfY, float* pfZ);
//typedef void(__thiscall* tCScreenSetDiffuseColor)(void* This, float r, float g, float b, float a);
//
//typedef void(__thiscall* tCScreenRenderLine3D)(void* This, float sx, float sy, float sz, float ex, float ey, float ez);
//static tCScreenSetDiffuseColor CScreenSetDiffuseColor;
//static tCScreenRenderLine3D CScreenRenderLine3D;
////#################################################################################################################################
//static void SetDiffuseColor(float r, float g, float b, float a)
//{
//	return Globals::CScreenSetDiffuseColor((void*)Globals::iCScreenInstance, r, g, b, a);
//}
////#################################################################################################################################
//static void RenderLine3D(float sx, float sy, float sz, float ex, float ey, float ez)
//{
//	return Globals::CScreenRenderLine3D((void*)Globals::iCScreenInstance, sx, sy, sz, ex, ey, ez);
//}



/*if (pCScreenProjectPosition != NULL) {
		CScreenProjectPosition = (tCScreenProjectPosition)(pCScreenProjectPosition);
	}
	if (pCPythonApplicationGetCenterPosition != NULL) {
		CPythonApplicationGetCenterPosition = (tCPythonApplicationGetCenterPosition)(pCPythonApplicationGetCenterPosition);
	}
	if (pCScreenSetDiffuseColor != NULL) {
		CScreenSetDiffuseColor = (tCScreenSetDiffuseColor)(pCScreenSetDiffuseColor);
	}
	if (pCScreenRenderLine3D != NULL) {
		CScreenRenderLine3D = (tCScreenRenderLine3D)(pCScreenRenderLine3D);
	}*/


	//#################################################################################################################################
		/*static void GetCenterPosition(D3DXVECTOR3* pPixelPosition)
		{
			return Globals::CPythonApplicationGetCenterPosition((void*)Globals::iCPythonApplicationInstance, pPixelPosition);
		}*/

		//#################################################################################################################################
		//static const D3DXMATRIX& GetTransform()
		//{
		//	DWORD* pCharInstance = GameFunctions::CharacterManagerGetInstancePtr(GameFunctions::PlayerGetMainCharacterIndex());
		//	auto Instance = pCharInstance + 520;//GLOBAL +544
		//	return Globals::CGetTransform(Instance);
		//}


//if (ImGui::Button("Test1", ImVec2(60, 0)))
//{
//	DWORD h = *reinterpret_cast<DWORD*>(Globals::iCPythonNetworkStreamInstance + 0x170);
//
//	Globals::PyCallClassMemberFunc((PyObject*)h, "SetSelectCharacterPhase", Py_BuildValue("()"));
//}
//if (ImGui::Button("Test2", ImVec2(60, 0)))
//{
//	DWORD h = *reinterpret_cast<DWORD*>(Globals::iCPythonNetworkStreamInstance + 0x170);
//
//
//	Globals::PyCallClassMemberFunc((PyObject*)h, "SetGamePhase", Py_BuildValue("()"));
//}
//if (ImGui::Button("Test3", ImVec2(60, 0)))
//{
//	PyRun_SimpleStringFlags("exec(compile(open('test2.py').read(), 'test2.py', 'exec'))", 0);
//}
//
//if (ImGui::Button("Test4", ImVec2(60, 0)))
//{
//	PyRun_SimpleStringFlags("exec(compile(open('test1.py').read(), 'test1.py', 'exec'))", 0);
//}
//DWORD h = *reinterpret_cast<DWORD*>(Globals::iCPythonNetworkStreamInstance + 0x170);
//
//
//
//
//Globals::PyCallClassMemberFunc((PyObject*)h, "SetLoadingPhase", Py_BuildValue("()"));

//DWORD h = *reinterpret_cast<DWORD*>(Globals::iCPythonNetworkStreamInstance + 0x184);
						//
						//Globals::PyCallClassMemberFunc((PyObject*)h, "LoadData", Py_BuildValue("(ii)", 0, 0));
						//]


//for (int i = 0; i < 99999; i++)
//{
//	const TMobTable* t = GameFunctions::NonPlayerGetTable(i);
//
//	if (t != NULL)
//	{
//		/*string g = StringExtension::StringFormat("%u\"\t\"%s\"\t\"%s\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\""
//			"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%s\"\t\""
//			"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\""
//			"%u\"\t\"%u\"\t\"%d\"\t\"%d\"\t\"%d\"\t\"%u\"\t\"%d\"\t\"%d\"\t\"%u\"\t\""
//
//			"%d\"\t\"%d\"\t\"%d\"\t\"%d\"\t\"%d\"\t\"%d\"\t\""
//			"%d\"\t\"%d\"\t\"%d\"\t\"%d\"\t\"%d\"\t\"%d\"\t\""
//			"%d\"\t\"%d\"\t\"%d\"\t\"%d\"\t\"%d\"\t\""
//			"%f\"\t\"%u\"\t\"%u\"\t\""
//
//			"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\""
//			"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\""
//			"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\"%u\"\t\""
//			"%u\"\t\"%u\"\t\"",
//
//
//			t->dwVnum, t->szName, t->szLocaleName, t->bType, t->bRank, t->bBattleType, t->bLevel, t->bSize, t->dwAIFlag, t->dwRaceFlag, t->dwImmuneFlag,
//			t->bOnClickType, t->bEmpire, t->dwDropItemVnum, t->dwResurrectionVnum, t->szFolder,
//			t->bStr, t->bDex, t->bCon, t->bInt, t->dwDamageRange[0], t->dwDamageRange[1], t->dwMaxHP, t->bRegenCycle, t->bRegenPercent, t->dwExp,
//
//			t->dwGoldMin, t->dwGoldMax, t->wDef, t->sAttackSpeed, t->sMovingSpeed, t->bAggresiveHPPct, t->wAggressiveSight, t->wAttackRange, t->dwPolymorphItemVnum,
//			t->cEnchants[0], t->cEnchants[1], t->cEnchants[2], t->cEnchants[3], t->cEnchants[4], t->cEnchants[5],
//			t->cResists[0], t->cResists[1], t->cResists[2], t->cResists[3], t->cResists[4], t->cResists[5],
//			t->cResists[6], t->cResists[7], t->cResists[8], t->cResists[9], t->cResists[10],
//			t->fDamMultiply, t->dwSummonVnum, t->dwDrainSP,
//
//			t->Skills[0].dwVnum, t->Skills[0].bLevel, t->Skills[1].dwVnum, t->Skills[1].bLevel, t->Skills[2].dwVnum, t->Skills[2].bLevel,
//			t->Skills[3].dwVnum, t->Skills[3].bLevel, t->Skills[4].dwVnum, t->Skills[4].bLevel,
//			t->bBerserkPoint, t->bStoneSkinPoint, t->bGodSpeedPoint, t->bDeathBlowPoint, t->bRevivePoint,
//			t->bMountCapacity, t->dwMobColor
//		);*/
//
//
//
//		string g = StringExtension::StringFormat("%u\"\t\"%s\"\t\"%u\"\t\"%u\"\t\"%u\""
//			,
//
//			t->dwVnum, t->szLocaleName, t->dwGoldMin, t->dwGoldMax, t->dwDropItemVnum
//
//		);
//
//
//		std::ofstream outfile;
//		outfile.open("protoX.txt", std::ios_base::app);
//		outfile << g;
//		outfile << "\n";
//	}
//}










//bool _fastcall Hooks::NewCNetworkStreamSendAeldra(void* This, void* EDX, int len, void* pDestBuf, bool instant)
//{
//	BYTE header;
//	memcpy(&header, pDestBuf, sizeof(header));
//
//	//if (header == 0x02 && len == 6)
//	//{
//	//	strncpy((char*)pDestBuf + 2, "\xB5", 1);
//	//}
//	if (header == 0x0A && len > 120)
//	{
//		for (int i = 0; i < len; i++)
//		{
//			BYTE check1 = 0;
//			BYTE check2 = 0;
//			BYTE check3 = 0;
//			BYTE check4 = 0;
//			memcpy(&check1, static_cast<char*>(pDestBuf) + i, sizeof(check1));
//			memcpy(&check2, static_cast<char*>(pDestBuf) + (i + 1), sizeof(check2));
//			memcpy(&check3, static_cast<char*>(pDestBuf) + (i + 2), sizeof(check3));
//			memcpy(&check4, static_cast<char*>(pDestBuf) + (i + 3), sizeof(check4));
//			if (check1 == 0xDD && check2 == 0xFC && check3 == 0xDF && check4 == 0xF9)
//			{
//				strncpy((char*)pDestBuf + (i), "\xBD\xDE\xA0\xFA", 4); //83 d8 9f fa
//				break;
//			}
//		}
//	}
//
//	bool ret = nCNetworkStreamSendAeldra(This, len, pDestBuf, 1);
//	//BYTE* destBuf = (BYTE*)pDestBuf;
//#ifdef DEVELOPER_MODE
//	PacketSniffer::Instance().ProcessSendPacket(len, (void*)pDestBuf, (DWORD)_ReturnAddress() - Globals::hEntryBaseAddress);
//#endif
//	return ret;
//}
//
////int _stdcall Hooks::NewCNetworkStreamSendAeldra(SOCKET s, const char* pDestBuf, int len, int flags)
////{
////	BYTE header;
////	memcpy(&header, pDestBuf, sizeof(header));
////
////	if (header == 0x02 && len == 6)
////	{
////		strncpy((char*)pDestBuf + 2, "\xA7", 1);
////	}
////	if (header == 0x0A && len > 150)
////	{
////		strncpy((char*)pDestBuf + (len - 85), "\x9C\xBF\xFE\xF9", 4);
////		//strncpy((char*)pDestBuf + (len - 85), "\xB1\xC4\x90\xFA", 4);
////	}
////
////	int ret = nCNetworkStreamSendAeldra(s, pDestBuf, len, flags);
////	BYTE* destBuf = (BYTE*)pDestBuf;
////#ifdef DEVELOPER_MODE
////	PacketSniffer::Instance().ProcessSendPacket(len, (void*)pDestBuf, (DWORD)_ReturnAddress() - Globals::hEntryBaseAddress);
////#endif
////	return ret;
////}