#pragma once
#include "..\framework.h"


inline void (*ActorProcEvent)(UObject*, UFunction*, void* Params);
void ActorProcEvent_Hk(UObject* Object, UFunction* Function, void* Params)
{
	if (Object && Function)
	{
		string FuncName = Function->GetName();

		if (FuncName == "ClientOnPawnDied")
		{
			std::cout << "ReturnAddress: " << std::hex << __int64(_ReturnAddress()) - ImageBase << dec << endl;
		}
	}
	return ActorProcEvent(Object, Function, Params);
}

inline void (*ProcEvent)(UObject*, UFunction*, void* Params);
void ProcEvent_Hk(UObject* Object, UFunction* Function, void* Params)
{
	if (Object && Function)
	{
		string FuncName = Function->GetName();

		if (FuncName == "ClientOnPawnDied")
		{
			std::cout << "ReturnAddress: " << std::hex << __int64(_ReturnAddress()) - ImageBase << dec << endl;
		}

		if (FuncName.contains("Deco")) {
			std::cout << FuncName << std::endl;
			std::cout << "ReturnAddress: " << std::hex << __int64(_ReturnAddress()) - ImageBase << dec << endl;
		}

		if (FuncName.contains("ServerEndEditingBuildingActor")) {
			std::cout << FuncName << std::endl;
			std::cout << "ReturnAddress: " << std::hex << __int64(_ReturnAddress()) - ImageBase << dec << endl;
		}
	}

	return ProcEvent(Object, Function, Params);
}