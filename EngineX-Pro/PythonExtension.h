#pragma once
class PythonExtension
{
public:
	static unordered_map<string, DWORD> ModulesMap;
	static map< string, string> functionPythonList;
	static const char* CheckImportNames(const char* name, PyMethodDef* methods)
	{
#if defined(PYTHON_ENABLE)
		if (methods == NULL)
		{
			return name;
		}
		if (name == "zipimport")
		{
			return name;
		}
		for (int i = 0;; i++)
		{
			if (methods[i].ml_name == NULL)
			{
				return name;
			}
			string functionName = methods[i].ml_name;

			string moduleName = name;

			if (functionName.length() > 7)
			{
				for (map<string, string>::iterator itor = functionPythonList.begin(); itor != functionPythonList.end(); itor++)
				{
					if (functionName == itor->first)
					{
						return (char*)itor->second.c_str();
					}
				}
			}
		}
#endif
		return name;
	}

	typedef PyObject* PythonModuleFunction(PyObject* poSelf, PyObject* PoArgs);

	static bool PyTuple_GetFloat(PyObject* poArgs, int pos, float* ret)
	{
#if defined(PYTHON_ENABLE)
		PyObject* poItem = PyTuple_GetItem(poArgs, pos);

		if (!poItem)
			return false;

		*ret = float(PyFloat_AsDouble(poItem));
		return true;
#endif
	}

	static bool PyTuple_GetInteger(PyObject* poItem, int pos, int* ret)
	{
#if defined(PYTHON_ENABLE)
		if (!poItem)
			return false;

		*ret = PyLong_AsLong(poItem);

#endif
		return true;
	}

	static bool PyTuple_GetString(PyObject* poItem, int pos, const char** ret)
	{
#if defined(PYTHON_ENABLE)
		if (!poItem)
			return false;

		if (!PyString_Check(poItem))
			return false;

		*ret = PyString_AsString(poItem);
#endif
		return true;
	}

	static int* GetPythonDoubleInt(DWORD addr)
	{
		int result[2];
#if defined(PYTHON_ENABLE)
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		PyObject* ret = func(NULL, NULL); //zmienilem to bo byl blad kompilacji //komar
		if (!PyTuple_GetInteger(ret, 0, &result[0]))
		{
			result[0] = 0;
		}
		if (!PyTuple_GetInteger(ret, 1, &result[1]))
		{
			result[1] = 0;
		}
		Py_DECREF(ret);
#endif
		return result;
	}

	static int GetPythonInt(DWORD addr)
	{
		int result;
#if defined(PYTHON_ENABLE)
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		PyObject* ret = func(NULL, NULL);
		ret->ob_type->tp_dealloc(ret);
		result = PyInt_AsLong(ret);
		Py_DECREF(ret);
#endif
		return result;
	}

	static float GetPythonFloat(DWORD addr)
	{
		float result;
#if defined(PYTHON_ENABLE)
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		PyObject* ret = func(NULL, NULL);
		PyTuple_GetFloat(ret, 0, &result);
		Py_DECREF(ret);
#endif
		return result;
	}

	static const char* GetPythonString0(DWORD addr)
	{
		const char* result;
#if defined(PYTHON_ENABLE)
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		PyObject* ret = func(NULL, NULL);
		if (!PyTuple_GetString(ret, 0, &result))
		{
			result = "";
		}
		Py_DECREF(ret);
#endif
		return result;
	}

	static const char* GetPythonString1(DWORD addr, int arg1)
	{
		const char* result;
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(1);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		PyObject* ret = func(NULL, args);
		if (!PyTuple_GetString(ret, 0, &result))
		{
			result = "";
		}
		Py_DECREF(ret);
		Py_DECREF(args);
#endif
		return result;
	}

	static const char* GetPythonString2(DWORD addr, int arg1, int arg2)
	{
		const char* result;
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PyTuple_SetItem(args, 1, PyInt_FromLong(arg2));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		PyObject* ret = func(NULL, args);
		if (!PyTuple_GetString(ret, 0, &result))
		{
			result = "";
		}
		Py_DECREF(ret);
		Py_DECREF(args);
#endif
		return result;
	}

	static int GetPythonInteger1(DWORD addr, int arg1)
	{
		int result;
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(1);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		PyObject* ret = func(NULL, args);
		result = PyInt_AsLong(ret);
		Py_DECREF(ret);
		Py_DECREF(args);
#endif
		return result;
	}

	static int GetPythonInteger2(DWORD addr, int arg1, int arg2)
	{
		int result;
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PyTuple_SetItem(args, 1, PyInt_FromLong(arg2));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		PyObject* ret = func(NULL, args);
		result = PyInt_AsLong(ret);
		Py_DECREF(ret);
		Py_DECREF(args);
#endif
		return result;
	}

	static int GetPythonInteger3(DWORD addr, int arg1, int arg2, int arg3)
	{
		int result;
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(3);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PyTuple_SetItem(args, 1, PyInt_FromLong(arg2));
		PyTuple_SetItem(args, 2, PyInt_FromLong(arg3));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		PyObject* ret = func(NULL, args);
		result = PyInt_AsLong(ret);
		Py_DECREF(ret);
		Py_DECREF(args);
#endif
		return result;
	}

	static D3DVECTOR GetPythonD3DVECTOR1(DWORD addr, int arg1)
	{
		D3DVECTOR result{ 0,0,0 };
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(1);
		printf("VID is %d\n", arg1);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		PyObject* ret = func(NULL, args);
		if (PyTuple_Size(ret) == 3)
		{
			printf("Size is 3\n");
			PyTuple_GetFloat(ret, 0, &result.x);
			PyTuple_GetFloat(ret, 1, &result.y);
			PyTuple_GetFloat(ret, 2, &result.z);
		}
		printf("D3DVector result X:%1.f, Y:%1.f, Z:%1.f\n", result.x, result.y, result.z);
		Py_DECREF(ret);
		Py_DECREF(args);
#endif
		return result;
	}

	static void CallPython(DWORD addr)
	{
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		func(NULL, NULL);
	}

	static void CallPythonFloat1(DWORD addr, float arg1)
	{
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(1);
		PyTuple_SetItem(args, 0, PyFloat_FromDouble(arg1));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		func(NULL, args);
		Py_DECREF(args);
#endif
	}

	static void CallPythonString2(DWORD addr, const char* arg1, const char* arg2)
	{
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyString_FromString(arg1));
		PyTuple_SetItem(args, 1, PyString_FromString(arg2));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		func(NULL, args);
		Py_DECREF(args);
#endif
	}

	static void CallPythonStringInt(DWORD addr, const char* arg1, int arg2)
	{
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyString_FromString(arg1));
		PyTuple_SetItem(args, 1, PyInt_FromLong(arg2));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		func(NULL, args);
		Py_DECREF(args);
#endif
	}

	static void CallPythonInteger1(DWORD addr, int arg1)
	{
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(1);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		func(NULL, args);
		Py_DECREF(args);
#endif
	}

	static void CallPythonInteger2(DWORD addr, int arg1, int arg2)
	{
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PyTuple_SetItem(args, 1, PyInt_FromLong(arg2));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		func(NULL, args);
		Py_DECREF(args);
#endif
	}

	static void CallPythonInteger3(DWORD addr, int arg1, int arg2, int arg3)
	{
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(3);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PyTuple_SetItem(args, 1, PyInt_FromLong(arg2));
		PyTuple_SetItem(args, 2, PyInt_FromLong(arg3));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		func(NULL, args);
		Py_DECREF(args);
#endif
	}

	static void CallPythonInteger4(DWORD addr, int arg1, int arg2, int arg3, int arg4)
	{
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(4);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PyTuple_SetItem(args, 1, PyInt_FromLong(arg2));
		PyTuple_SetItem(args, 2, PyInt_FromLong(arg3));
		PyTuple_SetItem(args, 3, PyInt_FromLong(arg4));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		func(NULL, args);
		Py_DECREF(args);
#endif
	}

	static void CallPythonInteger5(DWORD addr, int arg1, int arg2, int arg3, int arg4, int arg5)
	{
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(5);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PyTuple_SetItem(args, 1, PyInt_FromLong(arg2));
		PyTuple_SetItem(args, 2, PyInt_FromLong(arg3));
		PyTuple_SetItem(args, 3, PyInt_FromLong(arg4));
		PyTuple_SetItem(args, 4, PyInt_FromLong(arg4));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		func(NULL, args);
		Py_DECREF(args);
#endif
	}

	static void CallPythonIntIntString(DWORD addr, int arg1, int arg2, const char* arg3)
	{
#if defined(PYTHON_ENABLE)
		PyObject* args = PyTuple_New(3);
		PyTuple_SetItem(args, 0, PyInt_FromLong(arg1));
		PyTuple_SetItem(args, 1, PyInt_FromLong(arg2));
		PyTuple_SetItem(args, 2, PyString_FromString(arg3));
		PythonModuleFunction* func = (PythonModuleFunction*)(addr);
		func(NULL, args);
		Py_DECREF(args);
#endif
	}
};

std::unordered_map<string, DWORD> PythonExtension::ModulesMap;

map< string, string> PythonExtension::functionPythonList =
{
{ make_pair("Exist","pack") },
{ make_pair("Get","pack") },
{ make_pair("LogBox","dbg") },
{ make_pair("Trace","dbg") },
{ make_pair("Tracen","dbg") },
{ make_pair("TraceError","dbg") },
{ make_pair("RegisterExceptionString","dbg") },
{ make_pair("Enable","ime") },
{ make_pair("Disable","ime") },
{ make_pair("EnableCaptureInput","ime") },
{ make_pair("DisableCaptureInput","ime") },
{ make_pair("SetMax","ime") },
{ make_pair("SetUserMax","ime") },
{ make_pair("SetText","ime") },
{ make_pair("GetText","ime") },
{ make_pair("GetCodePage","ime") },
{ make_pair("GetCandidateCount","ime") },
{ make_pair("GetCandidate","ime") },
{ make_pair("GetCandidateSelection","ime") },
{ make_pair("GetReading","ime") },
{ make_pair("GetReadingError","ime") },
{ make_pair("EnableIME","ime") },
{ make_pair("DisableIME","ime") },
{ make_pair("GetInputMode","ime") },
{ make_pair("SetInputMode","ime") },
{ make_pair("SetNumberMode","ime") },
{ make_pair("SetStringMode","ime") },
{ make_pair("AddExceptKey","ime") },
{ make_pair("ClearExceptKey","ime") },
{ make_pair("MoveLeft","ime") },
{ make_pair("MoveRight","ime") },
{ make_pair("MoveHome","ime") },
{ make_pair("MoveEnd","ime") },
{ make_pair("SetCursorPosition","ime") },
{ make_pair("Delete","ime") },
{ make_pair("PasteString","ime") },
{ make_pair("PasteBackspace","ime") },
{ make_pair("PasteReturn","ime") },
{ make_pair("PasteTextFromClipBoard","ime") },
{ make_pair("EnablePaste","ime") },
{ make_pair("InitScreenEffect","grp") },
{ make_pair("Culling","grp") },
{ make_pair("ClearDepthBuffer","grp") },
{ make_pair("Identity","grp") },
{ make_pair("GenerateColor","grp") },
{ make_pair("PopState","grp") },
{ make_pair("PushState","grp") },
{ make_pair("PushMatrix","grp") },
{ make_pair("PopMatrix","grp") },
{ make_pair("Translate","grp") },
{ make_pair("Rotate","grp") },
{ make_pair("SetColorRenderState","grp") },
{ make_pair("SetAroundCamera","grp") },
{ make_pair("SetPositionCamera","grp") },
{ make_pair("SetEyeCamera","grp") },
{ make_pair("SetPerspective","grp") },
{ make_pair("SetOrtho2d","grp") },
{ make_pair("SetOrtho3d","grp") },
{ make_pair("SetColor","grp") },
{ make_pair("SetAlpha","grp") },
{ make_pair("SetDiffuseColor","grp") },
{ make_pair("SetClearColor","grp") },
{ make_pair("GetCursorPosition3d","grp") },
{ make_pair("SetCursorPosition","grp") },
{ make_pair("RenderLine","grp") },
{ make_pair("RenderBox","grp") },
{ make_pair("RenderRoundBox","grp") },
{ make_pair("RenderBox3d","grp") },
{ make_pair("RenderBar","grp") },
{ make_pair("RenderBar3d","grp") },
{ make_pair("RenderGradationBar","grp") },
{ make_pair("RenderCube","grp") },
{ make_pair("RenderDownButton","grp") },
{ make_pair("RenderUpButton","grp") },
{ make_pair("GetAvailableMemory","grp") },
{ make_pair("SaveScreenShot","grp") },
{ make_pair("SaveScreenShotToPath","grp") },
{ make_pair("SetGamma","grp") },
{ make_pair("SetInterfaceRenderState","grp") },
{ make_pair("SetGameRenderState","grp") },
{ make_pair("SetViewport","grp") },
{ make_pair("RestoreViewport","grp") },
{ make_pair("SetOmniLight","grp") },
{ make_pair("GetCameraPosition","grp") },
{ make_pair("GetTargetPosition","grp") },
{ make_pair("CreateTextBar","grp") },
{ make_pair("CreateBigTextBar","grp") },
{ make_pair("DestroyTextBar","grp") },
{ make_pair("RenderTextBar","grp") },
{ make_pair("TextBarTextOut","grp") },
{ make_pair("TextBarSetTextColor","grp") },
{ make_pair("TextBarGetTextExtent","grp") },
{ make_pair("ClearTextBar","grp") },
{ make_pair("SetTextBarClipRect","grp") },
{ make_pair("Render","grpImage") },
{ make_pair("SetPosition","grpImage") },
{ make_pair("Generate","grpImage") },
{ make_pair("GenerateExpanded","grpImage") },
{ make_pair("GenerateFromHandle","grpImage") },
{ make_pair("Delete","grpImage") },
{ make_pair("DeleteExpanded","grpImage") },
{ make_pair("SetFileName","grpImage") },
{ make_pair("SetOrigin","grpImage") },
{ make_pair("SetRotation","grpImage") },
{ make_pair("SetScale","grpImage") },
{ make_pair("SetRenderingRect","grpImage") },
{ make_pair("SetDiffuseColor","grpImage") },
{ make_pair("GetWidth","grpImage") },
{ make_pair("GetHeight","grpImage") },
{ make_pair("Update","grpText") },
{ make_pair("Render","grpText") },
{ make_pair("Generate","grpText") },
{ make_pair("Destroy","grpText") },
{ make_pair("SetFontName","grpText") },
{ make_pair("SetFontColor","grpText") },
{ make_pair("SetOutLineColor","grpText") },
{ make_pair("SetSecret","grpText") },
{ make_pair("SetOutline","grpText") },
{ make_pair("SetText","grpText") },
{ make_pair("GetText","grpText") },
{ make_pair("GetSize","grpText") },
{ make_pair("SetPosition","grpText") },
{ make_pair("ShowCursor","grpText") },
{ make_pair("HideCursor","grpText") },
{ make_pair("SetHorizontalAlign","grpText") },
{ make_pair("SetVerticalAlign","grpText") },
{ make_pair("SetMax","grpText") },
{ make_pair("GetSplitingTextLineCount","grpText") },
{ make_pair("GetSplitingTextLine","grpText") },
{ make_pair("PixelPositionToCharacterPosition","grpText") },
{ make_pair("ConvertMoneyText","grpText") },
{ make_pair("SetMouseHandler","wndMgr") },
{ make_pair("SetScreenSize","wndMgr") },
{ make_pair("GetScreenWidth","wndMgr") },
{ make_pair("GetScreenHeight","wndMgr") },
{ make_pair("AttachIcon","wndMgr") },
{ make_pair("DeattachIcon","wndMgr") },
{ make_pair("SetAttachingFlag","wndMgr") },
{ make_pair("GetAspect","wndMgr") },
{ make_pair("GetHyperlink","wndMgr") },
{ make_pair("OnceIgnoreMouseLeftButtonUpEvent","wndMgr") },
{ make_pair("ActivateEffect","wndMgr") },
{ make_pair("DeactivateEffect","wndMgr") },
{ make_pair("Register","wndMgr") },
{ make_pair("RegisterSlotWindow","wndMgr") },
{ make_pair("RegisterGridSlotWindow","wndMgr") },
{ make_pair("RegisterTextLine","wndMgr") },
{ make_pair("RegisterMarkBox","wndMgr") },
{ make_pair("RegisterImageBox","wndMgr") },
{ make_pair("RegisterExpandedImageBox","wndMgr") },
{ make_pair("RegisterAniImageBox","wndMgr") },
{ make_pair("RegisterButton","wndMgr") },
{ make_pair("RegisterRadioButton","wndMgr") },
{ make_pair("RegisterToggleButton","wndMgr") },
{ make_pair("RegisterDragButton","wndMgr") },
{ make_pair("RegisterBox","wndMgr") },
{ make_pair("RegisterBar","wndMgr") },
{ make_pair("RegisterLine","wndMgr") },
{ make_pair("RegisterBar3D","wndMgr") },
{ make_pair("RegisterNumberLine","wndMgr") },
{ make_pair("Destroy","wndMgr") },
{ make_pair("AddFlag","wndMgr") },
{ make_pair("IsRTL","wndMgr") },
{ make_pair("SetName","wndMgr") },
{ make_pair("GetName","wndMgr") },
{ make_pair("SetTop","wndMgr") },
{ make_pair("Show","wndMgr") },
{ make_pair("Hide","wndMgr") },
{ make_pair("IsShow","wndMgr") },
{ make_pair("SetParent","wndMgr") },
{ make_pair("SetPickAlways","wndMgr") },
{ make_pair("IsFocus","wndMgr") },
{ make_pair("SetFocus","wndMgr") },
{ make_pair("KillFocus","wndMgr") },
{ make_pair("Lock","wndMgr") },
{ make_pair("Unlock","wndMgr") },
{ make_pair("SetWindowSize","wndMgr") },
{ make_pair("SetWindowPosition","wndMgr") },
{ make_pair("GetWindowWidth","wndMgr") },
{ make_pair("GetWindowHeight","wndMgr") },
{ make_pair("GetWindowLocalPosition","wndMgr") },
{ make_pair("GetWindowGlobalPosition","wndMgr") },
{ make_pair("GetWindowRect","wndMgr") },
{ make_pair("SetWindowHorizontalAlign","wndMgr") },
{ make_pair("SetWindowVerticalAlign","wndMgr") },
{ make_pair("GetChildCount","wndMgr") },
{ make_pair("IsPickedWindow","wndMgr") },
{ make_pair("IsIn","wndMgr") },
{ make_pair("GetMouseLocalPosition","wndMgr") },
{ make_pair("GetMousePosition","wndMgr") },
{ make_pair("IsDragging","wndMgr") },
{ make_pair("SetLimitBias","wndMgr") },
{ make_pair("UpdateRect","wndMgr") },
{ make_pair("AppendSlot","wndMgr") },
{ make_pair("ArrangeSlot","wndMgr") },
{ make_pair("ClearSlot","wndMgr") },
{ make_pair("ClearAllSlot","wndMgr") },
{ make_pair("HasSlot","wndMgr") },
{ make_pair("SetSlot","wndMgr") },
{ make_pair("SetCardSlot","wndMgr") },
{ make_pair("SetSlotCount","wndMgr") },
{ make_pair("SetSlotCountNew","wndMgr") },
{ make_pair("SetSlotCoolTime","wndMgr") },
{ make_pair("SetToggleSlot","wndMgr") },
{ make_pair("ActivateSlot","wndMgr") },
{ make_pair("DeactivateSlot","wndMgr") },
{ make_pair("EnableSlot","wndMgr") },
{ make_pair("DisableSlot","wndMgr") },
{ make_pair("ShowSlotBaseImage","wndMgr") },
{ make_pair("HideSlotBaseImage","wndMgr") },
{ make_pair("SetSlotType","wndMgr") },
{ make_pair("SetSlotStyle","wndMgr") },
{ make_pair("SetSlotBaseImage","wndMgr") },
{ make_pair("SetCoverButton","wndMgr") },
{ make_pair("EnableCoverButton","wndMgr") },
{ make_pair("DisableCoverButton","wndMgr") },
{ make_pair("IsDisableCoverButton","wndMgr") },
{ make_pair("SetAlwaysRenderCoverButton","wndMgr") },
{ make_pair("AppendSlotButton","wndMgr") },
{ make_pair("AppendRequirementSignImage","wndMgr") },
{ make_pair("ShowSlotButton","wndMgr") },
{ make_pair("HideAllSlotButton","wndMgr") },
{ make_pair("ShowRequirementSign","wndMgr") },
{ make_pair("HideRequirementSign","wndMgr") },
{ make_pair("RefreshSlot","wndMgr") },
{ make_pair("SetUseMode","wndMgr") },
{ make_pair("SetUsableItem","wndMgr") },
{ make_pair("SelectSlot","wndMgr") },
{ make_pair("ClearSelected","wndMgr") },
{ make_pair("GetSelectedSlotCount","wndMgr") },
{ make_pair("GetSelectedSlotNumber","wndMgr") },
{ make_pair("IsSelectedSlot","wndMgr") },
{ make_pair("GetSlotCount","wndMgr") },
{ make_pair("LockSlot","wndMgr") },
{ make_pair("UnlockSlot","wndMgr") },
{ make_pair("SetColor","wndMgr") },
{ make_pair("SetMax","wndMgr") },
{ make_pair("SetHorizontalAlign","wndMgr") },
{ make_pair("SetVerticalAlign","wndMgr") },
{ make_pair("SetSecret","wndMgr") },
{ make_pair("SetOutline","wndMgr") },
{ make_pair("SetFeather","wndMgr") },
{ make_pair("SetMultiLine","wndMgr") },
{ make_pair("SetText","wndMgr") },
{ make_pair("SetFontName","wndMgr") },
{ make_pair("SetFontColor","wndMgr") },
{ make_pair("SetLimitWidth","wndMgr") },
{ make_pair("GetText","wndMgr") },
{ make_pair("GetTextSize","wndMgr") },
{ make_pair("ShowCursor","wndMgr") },
{ make_pair("HideCursor","wndMgr") },
{ make_pair("GetCursorPosition","wndMgr") },
{ make_pair("SetNumber","wndMgr") },
{ make_pair("SetNumberHorizontalAlignCenter","wndMgr") },
{ make_pair("SetNumberHorizontalAlignRight","wndMgr") },
{ make_pair("SetPath","wndMgr") },
{ make_pair("MarkBox_SetImage","wndMgr") },
{ make_pair("MarkBox_SetImageFilename","wndMgr") },
{ make_pair("MarkBox_Load","wndMgr") },
{ make_pair("MarkBox_SetIndex","wndMgr") },
{ make_pair("MarkBox_SetScale","wndMgr") },
{ make_pair("MarkBox_SetDiffuseColor","wndMgr") },
{ make_pair("LoadImage","wndMgr") },
{ make_pair("SetDiffuseColor","wndMgr") },
{ make_pair("GetWidth","wndMgr") },
{ make_pair("GetHeight","wndMgr") },
{ make_pair("SetScale","wndMgr") },
{ make_pair("SetOrigin","wndMgr") },
{ make_pair("SetRotation","wndMgr") },
{ make_pair("SetRenderingRect","wndMgr") },
{ make_pair("SetRenderingMode","wndMgr") },
{ make_pair("SetDelay","wndMgr") },
{ make_pair("AppendImage","wndMgr") },
{ make_pair("ResetFrame","wndMgr") },
{ make_pair("SetUpVisual","wndMgr") },
{ make_pair("SetOverVisual","wndMgr") },
{ make_pair("SetDownVisual","wndMgr") },
{ make_pair("SetDisableVisual","wndMgr") },
{ make_pair("GetUpVisualFileName","wndMgr") },
{ make_pair("GetOverVisualFileName","wndMgr") },
{ make_pair("GetDownVisualFileName","wndMgr") },
{ make_pair("Flash","wndMgr") },
{ make_pair("Enable","wndMgr") },
{ make_pair("Disable","wndMgr") },
{ make_pair("Down","wndMgr") },
{ make_pair("SetUp","wndMgr") },
{ make_pair("IsDown","wndMgr") },
{ make_pair("SetRestrictMovementArea","wndMgr") },
{ make_pair("EnableSlotCoverImage","wndMgr") },
{ make_pair("DisableSlotCoverImage","wndMgr") },
{ make_pair("ActivateChangeLookSlot","wndMgr") },
{ make_pair("DeactivateChangeLookSlot","wndMgr") },
{ make_pair("SetOutlineFlag","wndMgr") },
{ make_pair("ShowOverInWindowName","wndMgr") },
{ make_pair("SetSlotEnableEffect","wndMgr") },
{ make_pair("DisableSlotEnableEffect","wndMgr") },
{ make_pair("RegisterRenderTarget","wndMgr") },
{ make_pair("SetRenderTarget","wndMgr") },
{ make_pair("SetCanMouseEventSlot","wndMgr") },
{ make_pair("SetCantMouseEventSlot","wndMgr") },
{ make_pair("SetUsableSlotOnTopWnd","wndMgr") },
{ make_pair("SetUnusableSlotOnTopWnd","wndMgr") },
{ make_pair("IsDevStage","app") },
{ make_pair("IsTestStage","app") },
{ make_pair("IsLiveStage","app") },
{ make_pair("SetTextTailLivingTime","app") },
{ make_pair("EnablePerformanceTime","app") },
{ make_pair("SetHairColorEnable","app") },
{ make_pair("SetArmorSpecularEnable","app") },
{ make_pair("SetWeaponSpecularEnable","app") },
{ make_pair("SetSkillEffectUpgradeEnable","app") },
{ make_pair("SetTwoHandedWeaponAttSpeedDecreaseValue","app") },
{ make_pair("SetRideHorseEnable","app") },
{ make_pair("SetCameraMaxDistance","app") },
{ make_pair("SetMinFog","app") },
{ make_pair("SetFrameSkip","app") },
{ make_pair("GetImageInfo","app") },
{ make_pair("GetInfo","app") },
{ make_pair("UpdateGame","app") },
{ make_pair("RenderGame","app") },
{ make_pair("Loop","app") },
{ make_pair("Create","app") },
{ make_pair("Process","app") },
{ make_pair("Exit","app") },
{ make_pair("Abort","app") },
{ make_pair("SetMouseHandler","app") },
{ make_pair("IsExistFile","app") },
{ make_pair("GetFileList","app") },
{ make_pair("SetCamera","app") },
{ make_pair("GetCamera","app") },
{ make_pair("GetCameraPitch","app") },
{ make_pair("GetCameraRotation","app") },
{ make_pair("GetTime","app") },
{ make_pair("GetGlobalTime","app") },
{ make_pair("GetGlobalTimeStamp","app") },
{ make_pair("GetUpdateFPS","app") },
{ make_pair("GetRenderFPS","app") },
{ make_pair("RotateCamera","app") },
{ make_pair("PitchCamera","app") },
{ make_pair("ZoomCamera","app") },
{ make_pair("MovieRotateCamera","app") },
{ make_pair("MoviePitchCamera","app") },
{ make_pair("MovieZoomCamera","app") },
{ make_pair("MovieResetCamera","app") },
{ make_pair("GetAvailableTextureMemory","app") },
{ make_pair("GetRenderTime","app") },
{ make_pair("GetUpdateTime","app") },
{ make_pair("GetLoad","app") },
{ make_pair("GetFaceSpeed","app") },
{ make_pair("GetFaceCount","app") },
{ make_pair("SetFPS","app") },
{ make_pair("SetGlobalCenterPosition","app") },
{ make_pair("SetCenterPosition","app") },
{ make_pair("GetCursorPosition","app") },
{ make_pair("GetRandom","app") },
{ make_pair("IsWebPageMode","app") },
{ make_pair("ShowWebPage","app") },
{ make_pair("MoveWebPage","app") },
{ make_pair("HideWebPage","app") },
{ make_pair("IsPressed","app") },
{ make_pair("SetCursor","app") },
{ make_pair("GetCursor","app") },
{ make_pair("ShowCursor","app") },
{ make_pair("HideCursor","app") },
{ make_pair("IsShowCursor","app") },
{ make_pair("IsLiarCursorOn","app") },
{ make_pair("SetSoftwareCursor","app") },
{ make_pair("SetHardwareCursor","app") },
{ make_pair("SetConnectData","app") },
{ make_pair("GetConnectData","app") },
{ make_pair("GetRotatingDirection","app") },
{ make_pair("GetDegreeDifference","app") },
{ make_pair("Sleep","app") },
{ make_pair("SetDefaultFontName","app") },
{ make_pair("SetGuildSymbolPath","app") },
{ make_pair("EnableSpecialCameraMode","app") },
{ make_pair("SetCameraSpeed","app") },
{ make_pair("SaveCameraSetting","app") },
{ make_pair("LoadCameraSetting","app") },
{ make_pair("SetDefaultCamera","app") },
{ make_pair("SetCameraSetting","app") },
{ make_pair("SetSightRange","app") },
{ make_pair("IsFileExist","app") },
{ make_pair("OpenTextFile","app") },
{ make_pair("CloseTextFile","app") },
{ make_pair("GetTextFileLineCount","app") },
{ make_pair("GetTextFileLine","app") },
{ make_pair("GetLocaleServiceName","app") },
{ make_pair("GetLocaleName","app") },
{ make_pair("GetLocalePath","app") },
{ make_pair("ForceSetLocale","app") },
{ make_pair("LoadLocaleAddr","app") },
{ make_pair("LoadLocaleData","app") },
{ make_pair("SetCHEONMA","app") },
{ make_pair("IsCHEONMA","app") },
{ make_pair("GetDefaultCodePage","app") },
{ make_pair("SetControlFP","app") },
{ make_pair("SetSpecularSpeed","app") },
{ make_pair("testGetAccumulationTime","app") },
{ make_pair("testResetAccumulationTime","app") },
{ make_pair("testSetSpecularColor","app") },
{ make_pair("SetVisibleNotice","app") },
{ make_pair("IsVisibleNotice","app") },
{ make_pair("EnableTestServerFlag","app") },
{ make_pair("IsEnableTestServerFlag","app") },
{ make_pair("SetGuildMarkPath","app") },
{ make_pair("OnLogoUpdate","app") },
{ make_pair("OnLogoRender","app") },
{ make_pair("OnLogoOpen","app") },
{ make_pair("OnLogoClose","app") },
{ make_pair("ExecuteShell","app") },
{ make_pair("GetWidth","systemSetting") },
{ make_pair("GetHeight","systemSetting") },
{ make_pair("SetInterfaceHandler","systemSetting") },
{ make_pair("DestroyInterfaceHandler","systemSetting") },
{ make_pair("ReserveResource","systemSetting") },
{ make_pair("isInterfaceConfig","systemSetting") },
{ make_pair("SaveWindowStatus","systemSetting") },
{ make_pair("GetWindowStatus","systemSetting") },
{ make_pair("GetResolutionCount","systemSetting") },
{ make_pair("GetFrequencyCount","systemSetting") },
{ make_pair("GetCurrentResolution","systemSetting") },
{ make_pair("GetResolution","systemSetting") },
{ make_pair("GetFrequency","systemSetting") },
{ make_pair("ApplyConfig","systemSetting") },
{ make_pair("SetConfig","systemSetting") },
{ make_pair("SaveConfig","systemSetting") },
{ make_pair("GetConfig","systemSetting") },
{ make_pair("SetSaveID","systemSetting") },
{ make_pair("isSaveID","systemSetting") },
{ make_pair("GetSaveID","systemSetting") },
{ make_pair("GetMusicVolume","systemSetting") },
{ make_pair("GetSoundVolume","systemSetting") },
{ make_pair("SetMusicVolume","systemSetting") },
{ make_pair("SetSoundVolumef","systemSetting") },
{ make_pair("IsSoftwareCursor","systemSetting") },
{ make_pair("SetViewChatFlag","systemSetting") },
{ make_pair("IsViewChat","systemSetting") },
{ make_pair("SetAlwaysShowNameFlag","systemSetting") },
{ make_pair("GetAlwaysShowName","systemSetting") },
{ make_pair("SetShowDamageFlag","systemSetting") },
{ make_pair("IsShowDamage","systemSetting") },
{ make_pair("SetShowSalesTextFlag","systemSetting") },
{ make_pair("IsShowSalesText","systemSetting") },
{ make_pair("GetShadowLevel","systemSetting") },
{ make_pair("SetShadowLevel","systemSetting") },
{ make_pair("SetShopNamesRange","systemSetting") },
{ make_pair("GetShopNamesRange","systemSetting") },
{ make_pair("GetEffectMode","systemSetting") },
{ make_pair("SetEffectMode","systemSetting") },
{ make_pair("GetPetHideFlag","systemSetting") },
{ make_pair("SetPetHideFlag","systemSetting") },
{ make_pair("SetVisableMonsterRange","systemSetting") },
{ make_pair("GetVisableMonsterRange","systemSetting") },
{ make_pair("SetVisableShopRange","systemSetting") },
{ make_pair("GetVisableShopRange","systemSetting") },
{ make_pair("SetCountUseItem","systemSetting") },
{ make_pair("GetCountUseItem","systemSetting") },
{ make_pair("SetEffectLevel","systemSetting") },
{ make_pair("GetEffectLevel","systemSetting") },
{ make_pair("IsAffectInvisibility","chr") },
{ make_pair("DismountHorse","chr") },
{ make_pair("MountHorse","chr") },
{ make_pair("SetSash","chr") },
{ make_pair("Destroy","chr") },
{ make_pair("Update","chr") },
{ make_pair("Deform","chr") },
{ make_pair("Render","chr") },
{ make_pair("RenderCollision","chr") },
{ make_pair("CreateInstance","chr") },
{ make_pair("DeleteInstance","chr") },
{ make_pair("DeleteInstanceByFade","chr") },
{ make_pair("SelectInstance","chr") },
{ make_pair("HasInstance","chr") },
{ make_pair("IsEnemy","chr") },
{ make_pair("IsNPC","chr") },
{ make_pair("IsGameMaster","chr") },
{ make_pair("IsPartyMember","chr") },
{ make_pair("Select","chr") },
{ make_pair("SetAddRenderMode","chr") },
{ make_pair("SetBlendRenderMode","chr") },
{ make_pair("Unselect","chr") },
{ make_pair("Hide","chr") },
{ make_pair("Show","chr") },
{ make_pair("Pick","chr") },
{ make_pair("PickAll","chr") },
{ make_pair("SetArmor","chr") },
{ make_pair("SetWeapon","chr") },
{ make_pair("ChangeShape","chr") },
{ make_pair("SetRace","chr") },
{ make_pair("SetHair","chr") },
{ make_pair("ChangeHair","chr") },
{ make_pair("SetVirtualID","chr") },
{ make_pair("SetNameString","chr") },
{ make_pair("SetInstanceType","chr") },
{ make_pair("SetPixelPosition","chr") },
{ make_pair("SetDirection","chr") },
{ make_pair("Refresh","chr") },
{ make_pair("Revive","chr") },
{ make_pair("Die","chr") },
{ make_pair("AttachEffectByID","chr") },
{ make_pair("AttachEffectByName","chr") },
{ make_pair("LookAt","chr") },
{ make_pair("SetMotionMode","chr") },
{ make_pair("SetLoopMotion","chr") },
{ make_pair("BlendLoopMotion","chr") },
{ make_pair("PushOnceMotion","chr") },
{ make_pair("PushLoopMotion","chr") },
{ make_pair("GetPixelPosition","chr") },
{ make_pair("SetRotation","chr") },
{ make_pair("SetRotationAll","chr") },
{ make_pair("BlendRotation","chr") },
{ make_pair("GetRotation","chr") },
{ make_pair("GetRace","chr") },
{ make_pair("GetName","chr") },
{ make_pair("GetNameByVID","chr") },
{ make_pair("GetGuildID","chr") },
{ make_pair("GetProjectPosition","chr") },
{ make_pair("GetVirtualNumber","chr") },
{ make_pair("GetInstanceType","chr") },
{ make_pair("GetBoundBoxOnlyXY","chr") },
{ make_pair("RaceToJob","chr") },
{ make_pair("RaceToSex","chr") },
{ make_pair("testGetPKData","chr") },
{ make_pair("FaintTest","chr") },
{ make_pair("WeaponTraceSetTexture","chr") },
{ make_pair("WeaponTraceUseAlpha","chr") },
{ make_pair("WeaponTraceUseTexture","chr") },
{ make_pair("MoveToDestPosition","chr") },
{ make_pair("testSetComboType","chr") },
{ make_pair("testSetAddRenderMode","chr") },
{ make_pair("testSetModulateRenderMode","chr") },
{ make_pair("testSetAddRenderModeRGB","chr") },
{ make_pair("testSetModulateRenderModeRGB","chr") },
{ make_pair("testSetSpecularRenderMode","chr") },
{ make_pair("testSetSpecularRenderMode2","chr") },
{ make_pair("testRestoreRenderMode","chr") },
{ make_pair("testSetRideMan","chr") },
{ make_pair("IsAffect","chr") },
{ make_pair("SetEmpireNameMode","chrmgr") },
{ make_pair("GetVIDInfo","chrmgr") },
{ make_pair("GetPickedVID","chrmgr") },
{ make_pair("SetShapeModel","chrmgr") },
{ make_pair("AppendShapeSkin","chrmgr") },
{ make_pair("SetPathName","chrmgr") },
{ make_pair("LoadRaceData","chrmgr") },
{ make_pair("LoadLocalRaceData","chrmgr") },
{ make_pair("CreateRace","chrmgr") },
{ make_pair("SelectRace","chrmgr") },
{ make_pair("RegisterAttachingBoneName","chrmgr") },
{ make_pair("RegisterMotionMode","chrmgr") },
{ make_pair("SetMotionRandomWeight","chrmgr") },
{ make_pair("RegisterNormalAttack","chrmgr") },
{ make_pair("ReserveComboAttack","chrmgr") },
{ make_pair("RegisterComboAttack","chrmgr") },
{ make_pair("ReserveComboAttackNew","chrmgr") },
{ make_pair("RegisterComboAttackNew","chrmgr") },
{ make_pair("RegisterMotionData","chrmgr") },
{ make_pair("RegisterRaceName","chrmgr") },
{ make_pair("RegisterSpecialMob","chrmgr") },
{ make_pair("RegisterRaceSrcName","chrmgr") },
{ make_pair("ClearRaceName","chrmgr") },
{ make_pair("ReloadRaceName","chrmgr") },
{ make_pair("RegisterCacheMotionData","chrmgr") },
{ make_pair("SetAffect","chrmgr") },
{ make_pair("SetEmoticon","chrmgr") },
{ make_pair("IsPossibleEmoticon","chrmgr") },
{ make_pair("RegisterEffect","chrmgr") },
{ make_pair("RegisterCacheEffect","chrmgr") },
{ make_pair("RegisterPointEffect","chrmgr") },
{ make_pair("ShowPointEffect","chrmgr") },
{ make_pair("ToggleDirectionLine","chrmgr") },
{ make_pair("SetDustGap","chrmgr") },
{ make_pair("SetHorseDustGap","chrmgr") },
{ make_pair("RegisterTitleName","chrmgr") },
{ make_pair("RegisterNameColor","chrmgr") },
{ make_pair("RegisterTitleColor","chrmgr") },
{ make_pair("RegisterTitleColorNew","chrmgr") },
{ make_pair("GetAutoPotionInfo","player") },
{ make_pair("SetAutoPotionInfo","player") },
{ make_pair("IsTournamentMap","player") },
{ make_pair("PickCloseItem","player") },
{ make_pair("SetGameWindow","player") },
{ make_pair("RegisterEffect","player") },
{ make_pair("RegisterCacheEffect","player") },
{ make_pair("SetMouseState","player") },
{ make_pair("SetMouseFunc","player") },
{ make_pair("GetMouseFunc","player") },
{ make_pair("SetMouseMiddleButtonState","player") },
{ make_pair("SetMainCharacterIndex","player") },
{ make_pair("GetMainCharacterIndex","player") },
{ make_pair("GetMainCharacterName","player") },
{ make_pair("GetMainCharacterPosition","player") },
{ make_pair("IsMainCharacterIndex","player") },
{ make_pair("CanAttackInstance","player") },
{ make_pair("IsActingEmotion","player") },
{ make_pair("IsPVPInstance","player") },
{ make_pair("IsSameEmpire","player") },
{ make_pair("IsChallengeInstance","player") },
{ make_pair("IsRevengeInstance","player") },
{ make_pair("IsCantFightInstance","player") },
{ make_pair("GetCharacterDistance","player") },
{ make_pair("IsInSafeArea","player") },
{ make_pair("IsMountingHorse","player") },
{ make_pair("IsObserverMode","player") },
{ make_pair("ActEmotion","player") },
{ make_pair("ShowPlayer","player") },
{ make_pair("HidePlayer","player") },
{ make_pair("ComboAttack","player") },
{ make_pair("SetAutoCameraRotationSpeed","player") },
{ make_pair("SetAttackKeyState","player") },
{ make_pair("SetSingleDIKKeyState","player") },
{ make_pair("EndKeyWalkingImmediately","player") },
{ make_pair("StartMouseWalking","player") },
{ make_pair("EndMouseWalking","player") },
{ make_pair("ResetCameraRotation","player") },
{ make_pair("SetQuickCameraMode","player") },
{ make_pair("SetSkill","player") },
{ make_pair("GetSkillIndex","player") },
{ make_pair("GetSkillSlotIndex","player") },
{ make_pair("GetSkillGrade","player") },
{ make_pair("GetSkillLevel","player") },
{ make_pair("GetSkillCurrentEfficientPercentage","player") },
{ make_pair("GetSkillNextEfficientPercentage","player") },
{ make_pair("ClickSkillSlot","player") },
{ make_pair("ChangeCurrentSkillNumberOnly","player") },
{ make_pair("ClearSkillDict","player") },
{ make_pair("GetItemIndex","player") },
{ make_pair("GetItemFlags","player") },
{ make_pair("GetItemCount","player") },
{ make_pair("GetItemCountByVnum","player") },
{ make_pair("GetItemMetinSocket","player") },
{ make_pair("GetItemAttribute","player") },
{ make_pair("GetISellItemPrice","player") },
{ make_pair("MoveItem","player") },
{ make_pair("SendClickItemPacket","player") },
{ make_pair("GetName","player") },
{ make_pair("GetTheName","player") },
{ make_pair("GetJob","player") },
{ make_pair("GetRace","player") },
{ make_pair("GetPlayTime","player") },
{ make_pair("SetPlayTime","player") },
{ make_pair("IsSkillCoolTime","player") },
{ make_pair("GetSkillCoolTime","player") },
{ make_pair("IsSkillActive","player") },
{ make_pair("UseGuildSkill","player") },
{ make_pair("AffectIndexToSkillIndex","player") },
{ make_pair("GetEXP","player") },
{ make_pair("GetStatus","player") },
{ make_pair("SetStatus","player") },
{ make_pair("GetElk","player") },
{ make_pair("GetMoney","player") },
{ make_pair("GetCheque","player") },
{ make_pair("GetRP","player") },
{ make_pair("GetPO","player") },
{ make_pair("GetGuildID","player") },
{ make_pair("GetGuildName","player") },
{ make_pair("GetAlignmentData","player") },
{ make_pair("GetAlignmentColor","player") },
{ make_pair("RequestAddLocalQuickSlot","player") },
{ make_pair("RequestAddToEmptyLocalQuickSlot","player") },
{ make_pair("RequestDeleteGlobalQuickSlot","player") },
{ make_pair("RequestMoveGlobalQuickSlotToLocalQuickSlot","player") },
{ make_pair("RequestUseLocalQuickSlot","player") },
{ make_pair("LocalQuickSlotIndexToGlobalQuickSlotIndex","player") },
{ make_pair("GetQuickPage","player") },
{ make_pair("SetQuickPage","player") },
{ make_pair("GetLocalQuickSlot","player") },
{ make_pair("GetGlobalQuickSlot","player") },
{ make_pair("RemoveQuickSlotByValue","player") },
{ make_pair("isItem","player") },
{ make_pair("IsEquipmentSlot","player") },
{ make_pair("IsDSEquipmentSlot","player") },
{ make_pair("IsCostumeSlot","player") },
{ make_pair("IsValuableItem","player") },
{ make_pair("IsOpenPrivateShop","player") },
{ make_pair("IsBeltInventorySlot","player") },
{ make_pair("IsEquippingBelt","player") },
{ make_pair("IsAvailableBeltInventoryCell","player") },
{ make_pair("GetItemGrade","player") },
{ make_pair("CanRefine","player") },
{ make_pair("CanDetach","player") },
{ make_pair("CanUnlock","player") },
{ make_pair("CanAttachMetin","player") },
{ make_pair("IsRefineGradeScroll","player") },
{ make_pair("ClearTarget","player") },
{ make_pair("SetTarget","player") },
{ make_pair("OpenCharacterMenu","player") },
{ make_pair("Update","player") },
{ make_pair("Render","player") },
{ make_pair("Clear","player") },
{ make_pair("IsPartyMember","player") },
{ make_pair("IsPartyLeader","player") },
{ make_pair("IsPartyLeaderByPID","player") },
{ make_pair("GetPartyMemberHPPercentage","player") },
{ make_pair("GetPartyMemberState","player") },
{ make_pair("GetPartyMemberAffects","player") },
{ make_pair("RemovePartyMember","player") },
{ make_pair("ExitParty","player") },
{ make_pair("GetPKMode","player") },
{ make_pair("HasMobilePhoneNumber","player") },
{ make_pair("RegisterEmotionIcon","player") },
{ make_pair("GetEmotionIconImage","player") },
{ make_pair("GetItemTransmutate","player") },
{ make_pair("SetWeaponAttackBonusFlag","player") },
{ make_pair("ToggleCoolTime","player") },
{ make_pair("ToggleLevelLimit","player") },
{ make_pair("GetTargetVID","player") },
{ make_pair("SetItemData","player") },
{ make_pair("SetItemMetinSocket","player") },
{ make_pair("SetItemAttribute","player") },
{ make_pair("SetItemCount","player") },
{ make_pair("GetItemLink","player") },
{ make_pair("SlotTypeToInvenType","player") },
{ make_pair("SendDragonSoulRefine","player") },
{ make_pair("StackItems","player") },
{ make_pair("IsAntiFlagBySlot","player") },
{ make_pair("GetItemTypeBySlot","player") },
{ make_pair("GetItemSubTypeBySlot","player") },
{ make_pair("IsSameItemVnum","player") },
{ make_pair("IsShiningSlot","player") },
{ make_pair("SelectModel","player") },
{ make_pair("SetPart","player") },
{ make_pair("SetVisibility","player") },
{ make_pair("SetBackground","player") },
{ make_pair("SetVisitedOfflineShop","player") },
{ make_pair("InventoryLockCount","player") },
{ make_pair("SetUseSoundFileName","item") },
{ make_pair("SetDropSoundFileName","item") },
{ make_pair("SelectItem","item") },
{ make_pair("GetItemName","item") },
{ make_pair("GetItemDescription","item") },
{ make_pair("GetItemSummary","item") },
{ make_pair("GetIconImage","item") },
{ make_pair("GetIconImageFileName","item") },
{ make_pair("GetItemSize","item") },
{ make_pair("GetItemType","item") },
{ make_pair("GetItemSubType","item") },
{ make_pair("GetIBuyItemPrice","item") },
{ make_pair("GetISellItemPrice","item") },
{ make_pair("IsAntiFlag","item") },
{ make_pair("IsFlag","item") },
{ make_pair("IsWearableFlag","item") },
{ make_pair("Is1GoldItem","item") },
{ make_pair("GetLimit","item") },
{ make_pair("GetAffect","item") },
{ make_pair("GetValue","item") },
{ make_pair("GetSocket","item") },
{ make_pair("GetIconInstance","item") },
{ make_pair("GetUseType","item") },
{ make_pair("DeleteIconInstance","item") },
{ make_pair("IsEquipmentVID","item") },
{ make_pair("IsRefineScroll","item") },
{ make_pair("IsDetachScroll","item") },
{ make_pair("IsKey","item") },
{ make_pair("IsMetin","item") },
{ make_pair("CanAddToQuickSlotItem","item") },
{ make_pair("GetAntiFlag","item") },
{ make_pair("Update","item") },
{ make_pair("Render","item") },
{ make_pair("CreateItem","item") },
{ make_pair("DeleteItem","item") },
{ make_pair("Pick","item") },
{ make_pair("LoadItemTable","item") },
{ make_pair("GetItemsByName","item") },
{ make_pair("IsRefinable","item") },
{ make_pair("GetItemAntiFlag","item") },
{ make_pair("GetEventType","nonplayer") },
{ make_pair("GetEventTypeByVID","nonplayer") },
{ make_pair("GetLevelByVID","nonplayer") },
{ make_pair("GetGradeByVID","nonplayer") },
{ make_pair("GetTypeByVID","nonplayer") },
{ make_pair("GetMonsterName","nonplayer") },
{ make_pair("LoadNonPlayerData","nonplayer") },
{ make_pair("GetMonsterMaxHp","nonplayer") },
{ make_pair("GetRaceFlagByVID","nonplayer") },
{ make_pair("GetMonsterLevel","nonplayer") },
{ make_pair("IsMonsterBoss","nonplayer") },
{ make_pair("IsMonsterStone","nonplayer") },
{ make_pair("GetVnumByVID","nonplayer") },
{ make_pair("IsEnemy","nonplayer") },
{ make_pair("InitTrading","exchange") },
{ make_pair("isTrading","exchange") },
{ make_pair("GetLevelFromTarget","exchange") },
{ make_pair("GetElkFromSelf","exchange") },
{ make_pair("GetElkFromTarget","exchange") },
{ make_pair("GetItemVnumFromSelf","exchange") },
{ make_pair("GetItemVnumFromTarget","exchange") },
{ make_pair("GetItemCountFromSelf","exchange") },
{ make_pair("GetItemCountFromTarget","exchange") },
{ make_pair("GetAcceptFromSelf","exchange") },
{ make_pair("GetAcceptFromTarget","exchange") },
{ make_pair("GetNameFromSelf","exchange") },
{ make_pair("GetNameFromTarget","exchange") },
{ make_pair("GetItemMetinSocketFromTarget","exchange") },
{ make_pair("GetItemMetinSocketFromSelf","exchange") },
{ make_pair("GetItemAttributeFromTarget","exchange") },
{ make_pair("GetItemAttributeFromSelf","exchange") },
{ make_pair("GetItemTransmutateFromTarget","exchange") },
{ make_pair("GetItemTransmutateFromSelf","exchange") },
{ make_pair("GetElkMode","exchange") },
{ make_pair("SetElkMode","exchange") },
{ make_pair("GetChequeFromSelf","exchange") },
{ make_pair("GetChequeFromTarget","exchange") },
{ make_pair("SetChatColor","chat") },
{ make_pair("Clear","chat") },
{ make_pair("Close","chat") },
{ make_pair("CreateChatSet","chat") },
{ make_pair("Update","chat") },
{ make_pair("Render","chat") },
{ make_pair("SetBoardState","chat") },
{ make_pair("SetPosition","chat") },
{ make_pair("SetHeight","chat") },
{ make_pair("SetStep","chat") },
{ make_pair("ToggleChatMode","chat") },
{ make_pair("EnableChatMode","chat") },
{ make_pair("DisableChatMode","chat") },
{ make_pair("SetEndPos","chat") },
{ make_pair("GetLineCount","chat") },
{ make_pair("GetVisibleLineCount","chat") },
{ make_pair("GetLineStep","chat") },
{ make_pair("AppendChat","chat") },
{ make_pair("AppendChatWithDelay","chat") },
{ make_pair("ArrangeShowingChat","chat") },
{ make_pair("IgnoreCharacter","chat") },
{ make_pair("IsIgnoreCharacter","chat") },
{ make_pair("CreateWhisper","chat") },
{ make_pair("AppendWhisper","chat") },
{ make_pair("RenderWhisper","chat") },
{ make_pair("SetWhisperBoxSize","chat") },
{ make_pair("SetWhisperPosition","chat") },
{ make_pair("ClearWhisper","chat") },
{ make_pair("InitWhisper","chat") },
{ make_pair("GetLinkFromHyperlink","chat") },
{ make_pair("Clear","textTail") },
{ make_pair("UpdateAllTextTail","textTail") },
{ make_pair("UpdateShowingTextTail","textTail") },
{ make_pair("Render","textTail") },
{ make_pair("ShowCharacterTextTail","textTail") },
{ make_pair("ShowItemTextTail","textTail") },
{ make_pair("GetPosition","textTail") },
{ make_pair("IsChat","textTail") },
{ make_pair("ArrangeTextTail","textTail") },
{ make_pair("HideAllTextTail","textTail") },
{ make_pair("ShowAllTextTail","textTail") },
{ make_pair("ShowAllItemTextTail","textTail") },
{ make_pair("HideAllItemTextTail","textTail") },
{ make_pair("Pick","textTail") },
{ make_pair("SelectItemName","textTail") },
{ make_pair("EnablePKTitle","textTail") },
{ make_pair("RegisterCharacterTextTail","textTail") },
{ make_pair("RegisterChatTail","textTail") },
{ make_pair("RegisterInfoTail","textTail") },
{ make_pair("AttachTitle","textTail") },
{ make_pair("SendItemDestroyPacket","net") },
{ make_pair("GetBettingGuildWarValue","net") },
{ make_pair("EnableChatInsultFilter","net") },
{ make_pair("SetServerInfo","net") },
{ make_pair("GetServerInfo","net") },
{ make_pair("PreserveServerCommand","net") },
{ make_pair("GetPreservedServerCommand","net") },
{ make_pair("StartGame","net") },
{ make_pair("Warp","net") },
{ make_pair("IsTest","net") },
{ make_pair("SetMarkServer","net") },
{ make_pair("IsChatInsultIn","net") },
{ make_pair("IsInsultIn","net") },
{ make_pair("LoadInsultList","net") },
{ make_pair("UploadMark","net") },
{ make_pair("UploadSymbol","net") },
{ make_pair("GetGuildID","net") },
{ make_pair("GetEmpireID","net") },
{ make_pair("GetMainActorVID","net") },
{ make_pair("GetMainActorRace","net") },
{ make_pair("GetMainActorEmpire","net") },
{ make_pair("GetMainActorSkillGroup","net") },
{ make_pair("GetAccountCharacterSlotDataInteger","net") },
{ make_pair("GetAccountCharacterSlotDataString","net") },
{ make_pair("GetFieldMusicFileName","net") },
{ make_pair("GetFieldMusicVolume","net") },
{ make_pair("ToggleGameDebugInfo","net") },
{ make_pair("SetLoginInfo","net") },
{ make_pair("SetPhaseWindow","net") },
{ make_pair("ClearPhaseWindow","net") },
{ make_pair("SetServerCommandParserWindow","net") },
{ make_pair("SetAccountConnectorHandler","net") },
{ make_pair("SetHandler","net") },
{ make_pair("SetTCPRecvBufferSize","net") },
{ make_pair("SetTCPSendBufferSize","net") },
{ make_pair("SetUDPRecvBufferSize","net") },
{ make_pair("DirectEnter","net") },
{ make_pair("LogOutGame","net") },
{ make_pair("ExitGame","net") },
{ make_pair("ExitApplication","net") },
{ make_pair("ConnectTCP","net") },
{ make_pair("ConnectUDP","net") },
{ make_pair("ConnectToAccountServer","net") },
{ make_pair("SendLoginPacket","net") },
{ make_pair("SendChinaMatrixCardPacket","net") },
{ make_pair("SendRunupMatrixCardPacket","net") },
{ make_pair("SendNEWCIBNPasspodAnswerPacket","net") },
{ make_pair("SendSelectEmpirePacket","net") },
{ make_pair("SendSelectCharacterPacket","net") },
{ make_pair("SendChangeNamePacket","net") },
{ make_pair("SendCreateCharacterPacket","net") },
{ make_pair("SendDestroyCharacterPacket","net") },
{ make_pair("SendEnterGamePacket","net") },
{ make_pair("SendItemUsePacket","net") },
{ make_pair("SendItemUseToItemPacket","net") },
{ make_pair("SendItemDropPacket","net") },
{ make_pair("SendItemDropPacketNew","net") },
{ make_pair("SendElkDropPacket","net") },
{ make_pair("SendGoldDropPacketNew","net") },
{ make_pair("SendItemMovePacket","net") },
{ make_pair("SendItemPickUpPacket","net") },
{ make_pair("SendGiveItemPacket","net") },
{ make_pair("SetOfflinePhase","net") },
{ make_pair("Disconnect","net") },
{ make_pair("IsConnect","net") },
{ make_pair("SendChatPacket","net") },
{ make_pair("SendEmoticon","net") },
{ make_pair("SendWhisperPacket","net") },
{ make_pair("SendMobileMessagePacket","net") },
{ make_pair("SendCharacterPositionPacket","net") },
{ make_pair("SendShopEndPacket","net") },
{ make_pair("SendShopBuyPacket","net") },
{ make_pair("SendShopSellPacket","net") },
{ make_pair("SendShopSellPacketNew","net") },
{ make_pair("SendExchangeStartPacket","net") },
{ make_pair("SendExchangeItemAddPacket","net") },
{ make_pair("SendExchangeItemDelPacket","net") },
{ make_pair("SendExchangeElkAddPacket","net") },
{ make_pair("SendExchangeChequeAddPacket","net") },
{ make_pair("SendExchangeAcceptPacket","net") },
{ make_pair("SendExchangeExitPacket","net") },
{ make_pair("SendOnClickPacket","net") },
{ make_pair("RegisterEmoticonString","net") },
{ make_pair("SendMessengerAddByVIDPacket","net") },
{ make_pair("SendMessengerAddByNamePacket","net") },
{ make_pair("SendMessengerRemovePacket","net") },
{ make_pair("SendPartyInvitePacket","net") },
{ make_pair("SendPartyInviteAnswerPacket","net") },
{ make_pair("SendPartyExitPacket","net") },
{ make_pair("SendPartyRemovePacket","net") },
{ make_pair("SendPartySetStatePacket","net") },
{ make_pair("SendPartyUseSkillPacket","net") },
{ make_pair("SendPartyParameterPacket","net") },
{ make_pair("SendSafeboxSaveMoneyPacket","net") },
{ make_pair("SendSafeboxWithdrawMoneyPacket","net") },
{ make_pair("SendSafeboxCheckinPacket","net") },
{ make_pair("SendSafeboxCheckoutPacket","net") },
{ make_pair("SendSafeboxItemMovePacket","net") },
{ make_pair("SendMallCheckoutPacket","net") },
{ make_pair("SendAnswerMakeGuildPacket","net") },
{ make_pair("SendQuestInputStringPacket","net") },
{ make_pair("SendQuestConfirmPacket","net") },
{ make_pair("SendGuildAddMemberPacket","net") },
{ make_pair("SendGuildRemoveMemberPacket","net") },
{ make_pair("SendGuildChangeGradeNamePacket","net") },
{ make_pair("SendGuildChangeGradeAuthorityPacket","net") },
{ make_pair("SendGuildOfferPacket","net") },
{ make_pair("SendGuildPostCommentPacket","net") },
{ make_pair("SendGuildDeleteCommentPacket","net") },
{ make_pair("SendGuildRefreshCommentsPacket","net") },
{ make_pair("SendGuildChangeMemberGradePacket","net") },
{ make_pair("SendGuildUseSkillPacket","net") },
{ make_pair("SendGuildChangeMemberGeneralPacket","net") },
{ make_pair("SendGuildInviteAnswerPacket","net") },
{ make_pair("SendGuildChargeGSPPacket","net") },
{ make_pair("SendGuildDepositMoneyPacket","net") },
{ make_pair("SendGuildWithdrawMoneyPacket","net") },
{ make_pair("SendRequestRefineInfoPacket","net") },
{ make_pair("SendRefinePacket","net") },
{ make_pair("SendSelectItemPacket","net") },
{ make_pair("SetPacketSequenceMode","net") },
{ make_pair("SetEmpireLanguageMode","net") },
{ make_pair("SetSkillGroupFake","net") },
{ make_pair("SendGuildSymbol","net") },
{ make_pair("DisconnectUploader","net") },
{ make_pair("RecvGuildSymbol","net") },
{ make_pair("RegisterErrorLog","net") },
{ make_pair("SendTargetDropPacket","net") },
{ make_pair("DetachSoulStone","net") },
{ make_pair("CostumeColoring","net") },
{ make_pair("SendAddItemOfflineShopPacket","net") },
{ make_pair("SendRemoveGuestOfflineShopPacket","net") },
{ make_pair("SendBuyItemOfflineShopPacket","net") },
{ make_pair("SendOfflineShopStorageCheckoutPacket","net") },
{ make_pair("SendLotteryStartPacket","net") },
{ make_pair("SendLotteryStopPacket","net") },
{ make_pair("SendLotteryQuitPacket","net") },
{ make_pair("AddStoneExchangeItem","net") },
{ make_pair("DeleteStoneExchangeItem","net") },
{ make_pair("SendStoneExchangePacket","net") },
{ make_pair("SendRequestTreasureBoxLoot","net") },
{ make_pair("SendRequestNewInventoryCategory","net") },
{ make_pair("SendRequestTargetLootPacket","net") },
{ make_pair("ReloadActors","net") },
{ make_pair("SendItemShopPacket","net") },
{ make_pair("SetScale","miniMap") },
{ make_pair("ScaleUp","miniMap") },
{ make_pair("ScaleDown","miniMap") },
{ make_pair("SetMiniMapSize","miniMap") },
{ make_pair("SetCenterPosition","miniMap") },
{ make_pair("Destroy","miniMap") },
{ make_pair("Create","miniMap") },
{ make_pair("Update","miniMap") },
{ make_pair("Render","miniMap") },
{ make_pair("Show","miniMap") },
{ make_pair("Hide","miniMap") },
{ make_pair("isShow","miniMap") },
{ make_pair("GetInfo","miniMap") },
{ make_pair("LoadAtlas","miniMap") },
{ make_pair("UpdateAtlas","miniMap") },
{ make_pair("RenderAtlas","miniMap") },
{ make_pair("ShowAtlas","miniMap") },
{ make_pair("HideAtlas","miniMap") },
{ make_pair("isShowAtlas","miniMap") },
{ make_pair("IsAtlas","miniMap") },
{ make_pair("GetAtlasInfo","miniMap") },
{ make_pair("GetAtlasSize","miniMap") },
{ make_pair("AddWayPoint","miniMap") },
{ make_pair("RemoveWayPoint","miniMap") },
{ make_pair("RegisterAtlasWindow","miniMap") },
{ make_pair("UnregisterAtlasWindow","miniMap") },
{ make_pair("GetGuildAreaID","miniMap") },
{ make_pair("Push","profiler") },
{ make_pair("Pop","profiler") },
{ make_pair("RegisterEventSet","event") },
{ make_pair("RegisterEventSetFromString","event") },
{ make_pair("ClearEventSet","event") },
{ make_pair("SetRestrictedCount","event") },
{ make_pair("GetEventSetLocalYPosition","event") },
{ make_pair("AddEventSetLocalYPosition","event") },
{ make_pair("InsertText","event") },
{ make_pair("InsertTextInline","event") },
{ make_pair("UpdateEventSet","event") },
{ make_pair("RenderEventSet","event") },
{ make_pair("SetEventSetWidth","event") },
{ make_pair("Skip","event") },
{ make_pair("IsWait","event") },
{ make_pair("EndEventProcess","event") },
{ make_pair("SelectAnswer","event") },
{ make_pair("GetLineCount","event") },
{ make_pair("SetVisibleStartLine","event") },
{ make_pair("GetVisibleStartLine","event") },
{ make_pair("SetVisibleLineCount","event") },
{ make_pair("SetEventHandler","event") },
{ make_pair("SetInterfaceWindow","event") },
{ make_pair("SetLeftTimeString","event") },
{ make_pair("QuestButtonClick","event") },
{ make_pair("Destroy","event") },
{ make_pair("RegisterEffect","effect") },
{ make_pair("CreateEffect","effect") },
{ make_pair("DeleteEffect","effect") },
{ make_pair("SetPosition","effect") },
{ make_pair("RegisterIndexedFlyData","effect") },
{ make_pair("Update","effect") },
{ make_pair("Render","effect") },
{ make_pair("Update","fly") },
{ make_pair("Render","fly") },
{ make_pair("PlaySound","snd") },
{ make_pair("PlaySound3D","snd") },
{ make_pair("PlayMusic","snd") },
{ make_pair("FadeInMusic","snd") },
{ make_pair("FadeOutMusic","snd") },
{ make_pair("FadeOutAllMusic","snd") },
{ make_pair("FadeLimitOutMusic","snd") },
{ make_pair("StopAllSound","snd") },
{ make_pair("SetMusicVolumef","snd") },
{ make_pair("SetMusicVolume","snd") },
{ make_pair("SetSoundVolumef","snd") },
{ make_pair("SetSoundVolume","snd") },
{ make_pair("SetSoundScale","snd") },
{ make_pair("SetAmbienceSoundScale","snd") },
{ make_pair("Update","eventMgr") },
{ make_pair("Open","shop") },
{ make_pair("Close","shop") },
{ make_pair("IsOpen","shop") },
{ make_pair("IsPrivateShop","shop") },
{ make_pair("IsMainPlayerPrivateShop","shop") },
{ make_pair("GetItemID","shop") },
{ make_pair("GetItemCount","shop") },
{ make_pair("GetItemPrice","shop") },
{ make_pair("GetItemPriceNew","shop") },
{ make_pair("GetItemCurrency","shop") },
{ make_pair("GetItemEventMaxBuyCount","shop") },
{ make_pair("GetItemMetinSocket","shop") },
{ make_pair("GetItemAttribute","shop") },
{ make_pair("GetTabCount","shop") },
{ make_pair("GetTabName","shop") },
{ make_pair("GetTabCoinType","shop") },
{ make_pair("GetItemTransmutate","shop") },
{ make_pair("ClearPrivateShopStock","shop") },
{ make_pair("AddPrivateShopItemStock","shop") },
{ make_pair("DelPrivateShopItemStock","shop") },
{ make_pair("GetPrivateShopItemPrice","shop") },
{ make_pair("BuildPrivateShop","shop") },
{ make_pair("SetPathName","skill") },
{ make_pair("RegisterSkill","skill") },
{ make_pair("LoadSkillData","skill") },
{ make_pair("ClearSkillData","skill") },
{ make_pair("GetSkillName","skill") },
{ make_pair("GetSkillDescription","skill") },
{ make_pair("GetSkillType","skill") },
{ make_pair("GetSkillConditionDescriptionCount","skill") },
{ make_pair("GetSkillConditionDescription","skill") },
{ make_pair("GetSkillAffectDescriptionCount","skill") },
{ make_pair("GetSkillAffectDescription","skill") },
{ make_pair("GetSkillCoolTime","skill") },
{ make_pair("GetSkillNeedSP","skill") },
{ make_pair("GetSkillContinuationSP","skill") },
{ make_pair("GetSkillMaxLevel","skill") },
{ make_pair("GetSkillLevelUpPoint","skill") },
{ make_pair("GetSkillLevelLimit","skill") },
{ make_pair("IsSkillRequirement","skill") },
{ make_pair("GetSkillRequirementData","skill") },
{ make_pair("GetSkillRequireStatCount","skill") },
{ make_pair("GetSkillRequireStatData","skill") },
{ make_pair("CanLevelUpSkill","skill") },
{ make_pair("IsLevelUpSkill","skill") },
{ make_pair("CheckRequirementSueccess","skill") },
{ make_pair("GetNeedCharacterLevel","skill") },
{ make_pair("IsToggleSkill","skill") },
{ make_pair("IsUseHPSkill","skill") },
{ make_pair("IsStandingSkill","skill") },
{ make_pair("CanUseSkill","skill") },
{ make_pair("GetIconName","skill") },
{ make_pair("GetIconImage","skill") },
{ make_pair("GetIconImageNew","skill") },
{ make_pair("GetIconInstance","skill") },
{ make_pair("GetIconInstanceNew","skill") },
{ make_pair("DeleteIconInstance","skill") },
{ make_pair("GetGradeData","skill") },
{ make_pair("GetNewAffectDataCount","skill") },
{ make_pair("GetNewAffectData","skill") },
{ make_pair("GetDuration","skill") },
{ make_pair("TEST","skill") },
{ make_pair("GetQuestCount","quest") },
{ make_pair("GetQuestData","quest") },
{ make_pair("GetQuestIndex","quest") },
{ make_pair("GetQuestLastTime","quest") },
{ make_pair("Clear","quest") },
{ make_pair("IsSoftwareTiling","background") },
{ make_pair("EnableSoftwareTiling","background") },
{ make_pair("EnableSnow","background") },
{ make_pair("GlobalPositionToLocalPosition","background") },
{ make_pair("GlobalPositionToMapInfo","background") },
{ make_pair("GetRenderShadowTime","background") },
{ make_pair("LoadMap","background") },
{ make_pair("Destroy","background") },
{ make_pair("RegisterEnvironmentData","background") },
{ make_pair("SetEnvironmentData","background") },
{ make_pair("GetCurrentMapName","background") },
{ make_pair("GetPickingPoint","background") },
{ make_pair("BeginEnvironment","background") },
{ make_pair("EndEnvironment","background") },
{ make_pair("SetCharacterDirLight","background") },
{ make_pair("SetBackgroundDirLight","background") },
{ make_pair("Initialize","background") },
{ make_pair("Update","background") },
{ make_pair("Render","background") },
{ make_pair("RenderPCBlocker","background") },
{ make_pair("RenderCollision","background") },
{ make_pair("RenderSky","background") },
{ make_pair("RenderCloud","background") },
{ make_pair("RenderWater","background") },
{ make_pair("RenderEffect","background") },
{ make_pair("RenderBeforeLensFlare","background") },
{ make_pair("RenderAfterLensFlare","background") },
{ make_pair("RenderCharacterShadowToTexture","background") },
{ make_pair("RenderDungeon","background") },
{ make_pair("GetHeight","background") },
{ make_pair("SetShadowLevel","background") },
{ make_pair("SetVisiblePart","background") },
{ make_pair("GetShadowMapColor","background") },
{ make_pair("SetSplatLimit","background") },
{ make_pair("GetRenderedSplatNum","background") },
{ make_pair("GetRenderedGraphicThingInstanceNum","background") },
{ make_pair("SelectViewDistanceNum","background") },
{ make_pair("SetViewDistanceSet","background") },
{ make_pair("GetFarClip","background") },
{ make_pair("GetDistanceSetInfo","background") },
{ make_pair("SetBGLoading","background") },
{ make_pair("SetRenderSort","background") },
{ make_pair("SetTransparentTree","background") },
{ make_pair("SetXMasTree","background") },
{ make_pair("RegisterDungeonMapName","background") },
{ make_pair("VisibleGuildArea","background") },
{ make_pair("DisableGuildArea","background") },
{ make_pair("WarpTest","background") },
{ make_pair("RemoveFriend","messenger") },
{ make_pair("IsFriendByName","messenger") },
{ make_pair("Destroy","messenger") },
{ make_pair("RefreshGuildMember","messenger") },
{ make_pair("SetMessengerHandler","messenger") },
{ make_pair("SendCloseRequest","sash") },
{ make_pair("Add","sash") },
{ make_pair("Remove","sash") },
{ make_pair("GetPrice","sash") },
{ make_pair("GetAttachedItem","sash") },
{ make_pair("GetResultItem","sash") },
{ make_pair("SendRefineRequest","sash") },
{ make_pair("AddArmorEffect","shining") },
{ make_pair("AddWeaponEffect","shining") },
{ make_pair("AddMDEWeapon","shining") },
{ make_pair("Clear","shining") },
{ make_pair("Get","blocksystem") },
{ make_pair("Send","blocksystem") },
{ make_pair("isBlocked","blocksystem") },
{ make_pair("GetCurrentSafeboxSize","safebox") },
{ make_pair("GetItemID","safebox") },
{ make_pair("GetItemCount","safebox") },
{ make_pair("GetItemFlags","safebox") },
{ make_pair("GetItemMetinSocket","safebox") },
{ make_pair("GetItemAttribute","safebox") },
{ make_pair("GetMoney","safebox") },
{ make_pair("GetItemTransmutate","safebox") },
{ make_pair("GetMallItemID","safebox") },
{ make_pair("GetMallItemCount","safebox") },
{ make_pair("GetMallItemMetinSocket","safebox") },
{ make_pair("GetMallItemAttribute","safebox") },
{ make_pair("GetMallSize","safebox") },
{ make_pair("IsGuildEnable","guild") },
{ make_pair("GuildIDToMarkID","guild") },
{ make_pair("GetMarkImageFilenameByMarkID","guild") },
{ make_pair("GetMarkIndexByMarkID","guild") },
{ make_pair("GetGuildID","guild") },
{ make_pair("HasGuildLand","guild") },
{ make_pair("GetGuildName","guild") },
{ make_pair("GetGuildMasterName","guild") },
{ make_pair("GetEnemyGuildName","guild") },
{ make_pair("GetGuildMoney","guild") },
{ make_pair("GetGuildBoardCommentCount","guild") },
{ make_pair("GetGuildBoardCommentData","guild") },
{ make_pair("GetGuildLevel","guild") },
{ make_pair("GetGuildExperience","guild") },
{ make_pair("GetGuildMemberCount","guild") },
{ make_pair("GetGuildMemberLevelSummary","guild") },
{ make_pair("GetGuildMemberLevelAverage","guild") },
{ make_pair("GetGuildExperienceSummary","guild") },
{ make_pair("GetGuildSkillPoint","guild") },
{ make_pair("GetDragonPowerPoint","guild") },
{ make_pair("GetGuildSkillLevel","guild") },
{ make_pair("GetSkillLevel","guild") },
{ make_pair("GetSkillMaxLevelNew","guild") },
{ make_pair("SetSkillIndex","guild") },
{ make_pair("GetSkillIndex","guild") },
{ make_pair("GetGradeData","guild") },
{ make_pair("GetGradeName","guild") },
{ make_pair("GetMemberCount","guild") },
{ make_pair("GetMemberData","guild") },
{ make_pair("MemberIndexToPID","guild") },
{ make_pair("IsMember","guild") },
{ make_pair("IsMemberByName","guild") },
{ make_pair("MainPlayerHasAuthority","guild") },
{ make_pair("Destroy","guild") },
{ make_pair("GetNewGuildData","guild") },
{ make_pair("Create","ServerStateChecker") },
{ make_pair("Update","ServerStateChecker") },
{ make_pair("Request","ServerStateChecker") },
{ make_pair("AddChannel","ServerStateChecker") },
{ make_pair("Initialize","ServerStateChecker") },

};
