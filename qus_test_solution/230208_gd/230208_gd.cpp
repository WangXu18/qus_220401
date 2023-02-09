// 230208_gd.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <strsafe.h>
#include <conio.h>

#define BUFSIZE 4096

VOID GetAnswerToRequest(LPTSTR chRequest, LPTSTR chReply, LPDWORD pchBytes) {
  _tprintf(TEXT("%s\n"), chRequest);
  StringCchCopy(chReply, BUFSIZE, TEXT("Default answer from server"));
  *pchBytes = (lstrlen(chReply) + 1) * sizeof(TCHAR);
}

DWORD WINAPI InstanceThread(LPVOID lpvParam) {
  TCHAR chRequest[BUFSIZE];
  TCHAR chReply[BUFSIZE];
  DWORD cbBytesRead, cbReplyBytes, cbWritten;
  BOOL fSuccess;
  HANDLE hPipe;

  // The thread's parameter is a handle to a pipe instance.   

  hPipe = (HANDLE)lpvParam;

  while (1)
  {
	// Read client requests from the pipe.   
	fSuccess = ReadFile(
	  hPipe,        // handle to pipe   
	  chRequest,    // buffer to receive data   
	  BUFSIZE * sizeof(TCHAR), // size of buffer   
	  &cbBytesRead, // number of bytes read   
	  NULL);        // not overlapped I/O   

	if (!fSuccess || cbBytesRead == 0)
	  break;
	//printf((const char*)chRequest);
	std::cout << *chRequest << std::endl;

	GetAnswerToRequest(chRequest, chReply, &cbReplyBytes);

	// Write the reply to the pipe.   
	fSuccess = WriteFile(
	  hPipe,        // handle to pipe   
	  chReply,      // buffer to write from   
	  cbReplyBytes, // number of bytes to write   
	  &cbWritten,   // number of bytes written   
	  NULL);        // not overlapped I/O   

	if (!fSuccess || cbReplyBytes != cbWritten) break;
  }

  // Flush the pipe to allow the client to read the pipe's contents   
  // before disconnecting. Then disconnect the pipe, and close the   
  // handle to this pipe instance.   

  FlushFileBuffers(hPipe);
  DisconnectNamedPipe(hPipe);
  CloseHandle(hPipe);

  return 1;
}


int main()
{
  BOOL fConnected;
  DWORD dwThreadId;
  HANDLE hPipe, hThread;
  LPCWSTR lpPipeName = TEXT("\\\\.\\pipe\\mynamepipe");

  while (1)
  {
	hPipe = CreateNamedPipe(lpPipeName, PIPE_ACCESS_DUPLEX,
							PIPE_TYPE_MESSAGE|PIPE_READMODE_MESSAGE|PIPE_WAIT,
							PIPE_UNLIMITED_INSTANCES, BUFSIZE, BUFSIZE, 0, NULL);

	if (hPipe == INVALID_HANDLE_VALUE) {
	  std::cout << "create pipe failed" << std::endl;
	  return 0;
	}

	fConnected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
	if (fConnected) {
	  hThread = CreateThread(NULL, 0, InstanceThread, (LPVOID)hPipe, 0, &dwThreadId);
	  if (hThread == NULL) {
		std::cout << "create thread failed" << std::endl;
		return 0;
	  }
	  else {
		::CloseHandle(hThread);
	  }
	} else {
	  ::CloseHandle(hPipe);
	}
  }
}

