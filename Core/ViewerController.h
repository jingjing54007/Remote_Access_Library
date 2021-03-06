#pragma once

namespace SL {
	namespace Remote_Access_Library {
		namespace Network {
			struct Client_Config;
		}
		namespace UI {
			class ViewerControllerImpl;
			class ViewerController {
				ViewerControllerImpl* _ViewerControllerImpl = nullptr;
			public:
				ViewerController(std::shared_ptr<Network::Client_Config> config, const char*  dst_host);
				~ViewerController();
			};
		}
	}
}
