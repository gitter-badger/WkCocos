#ifndef __LOADING_ENTITY_PRLEOAD_H__
#define __LOADING_ENTITY_PRELOAD_H__

#include "cocos2d.h"

#include "entityx/entityx.h"
//#include "WkCocos/Loading/Events/Loaded.h"

#include "curl/curl.h"

namespace WkCocos 
{
	namespace Loading
	{
		class Preload : public entityx::Manager
			{
			public:
				explicit Preload(unsigned short  concurrent_downloads,
					unsigned short  concurrent_loads,
					std::function<void(float)> progress_callback,
					std::function<void()> error_callback
					);

				//scheduel the load in memory of a data.
				//DataLoad Event is sent when the load finishes.
				bool addDataLoad(const std::vector<std::string> &  filepath);
				
				virtual ~Preload();

				entityx::ptr<entityx::EventManager> getEventManager()
				{
					return event_manager;
				}

			protected:
				void configure() override;

				void initialize() override;

				void update(double dt) override;

				unsigned short m_concurrent_downloads;
				unsigned short m_concurrent_loads;
				std::function<void()> m_error_callback;
				std::function<void(float)> m_progress_callback;

				
			};

	} // namespace Loading
}  // namespace WkCocos

#endif //__LOADING_ENTITY_PRELOAD_H__
