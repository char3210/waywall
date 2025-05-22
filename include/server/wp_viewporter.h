#ifndef WAYWALL_SERVER_WP_VIEWPORTER_H
#define WAYWALL_SERVER_WP_VIEWPORTER_H

#include "config/config.h"
#include <wayland-server-core.h>
#include <wayland-util.h>

struct server_viewporter {
    struct wl_global *global;

    struct server *server;
};

struct server_viewporter *server_viewporter_create(struct server *server,
                                                   struct config *cfg);

#endif
