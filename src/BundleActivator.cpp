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
#include "Poco/StreamCopier.h"
#include <vector>
#include <set>
#include <iostream>
#include <memory>

//#include "lua.hpp"
#include "selene.h"

using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace Luama {

struct Persistence {
	int writes = 0;

	std::string readString(std::string key) { return key + "'s value"; }
	int readInt(std::string key) { return 42; }

	void writeString(std::string key, std::string value) { writes++; }
	void writeInt(std::string key, int value) { writes++; }
};

struct Radio_TunerInfo {
	int uid;
	std::string psName;
};
/*
struct Radio {
	sel::function<void(Radio_TunerInfo&)> callback;

	void subscribe(sel::function<void(Radio_TunerInfo&)> const &cb ) {
		callback = cb;
	}

	void unsubscribe(sel::function<void(Radio_TunerInfo&)> const &cb) {
		callback = nullptr;
	}

	void notify(Radio_TunerInfo& info) { 
		if(callback)
			callback(info);
	}
};
*/

class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
		//pState = luaL_newstate();
		//luaL_openlibs(pState);
	}
	
	~BundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		std::cout << "hello world from c++" << std::endl;

		try {
#if __cplusplus < 201103L
        std::auto_ptr<std::istream> pStream(pContext->thisBundle()->getResource("hello.lua"));
#else
        std::unique_ptr<std::istream> pStream(pContext->thisBundle()->getResource("hello.lua"));
#endif
		if (pStream.get())
		{
			std::string data;
			Poco::StreamCopier::copyToString(*pStream, data);
			std::cout << "data:"<< data << std::endl;

			sel::State state{true};

			Persistence pers;

			state["persistence"].SetObj(pers, "readString", &Persistence::readString,
											"readInt", &Persistence::readInt,
											"writeString", &Persistence::writeString,
											"writeInt", &Persistence::writeInt,
											"writes", &Persistence::writes);

			/*state["Radio"].SetClass<Radio>("subscribe", &Radio::subscribe,
												"unsubscribe", &Radio::unsubscribe,
												"notify", &Radio::notify);*/
			state(data.c_str());



			//luaL_dostring(pState, data.c_str());
		}

		}catch (Poco::Exception& ex) {
			std::cout<<ex.message()<<std::endl;
		}
		
		//luaL_dofile(pState, "hello.lua");
	}
		
	void stop(BundleContext::Ptr pContext)
	{
	}
	
private:
	//lua_State *pState;
};


 } // namespace Luama


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(Luama::BundleActivator)
POCO_END_MANIFEST
