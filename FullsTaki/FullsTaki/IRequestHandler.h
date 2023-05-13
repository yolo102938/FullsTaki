#pragma once
#include "RequestTypes.hpp"
#include <WinSock2.h>
#include "incs.h"

using std::exception;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo, const SOCKET) const = 0;
};