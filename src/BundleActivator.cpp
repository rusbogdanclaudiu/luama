//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/Format.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Util/Timer.h"
#include <vector>
#include <set>
#include <iostream>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace Luama {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
		pState = luaL_newstate();
		luaL_openlibs(pState);
	}
	
	~BundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		std::cout << "hello world from c++" << std::endl;
		luaL_dofile(pState, "hello.lua");
	}
		
	void stop(BundleContext::Ptr pContext)
	{
	}
	
private:
	lua_State *pState;
};


 } // namespace Luama


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(Luama::BundleActivator)
POCO_END_MANIFEST
