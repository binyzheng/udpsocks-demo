#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

namespace SN
{
#define udpsocks_VERSION_MAJOR 0
#define udpsocks_VERSION_MINOR 3
#define udpsocks_VERSION_PATCH 0
// note that each component is limited into [0-99] range by design
#define udpsocks_VERSION (((udpsocks_VERSION_MAJOR) * 10000) + ((udpsocks_VERSION_MINOR) * 100) + (udpsocks_VERSION_PATCH))
}

#endif
