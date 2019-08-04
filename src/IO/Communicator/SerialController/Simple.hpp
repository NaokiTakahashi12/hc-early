
 /**
   *
   * @file Simple.hpp
   * @brief Simple serial communication class
   * @author Naoki Takahashi
   *
   **/

#pragma once

#include "SerialControllerBase.hpp"

namespace IO {
	namespace Communicator {
		namespace SerialController {
			class Simple final : public SerialControllerBase {
				public :
					~Simple();

					void launch() override,
						 async_launch() override;
			};
		}
	}
}

