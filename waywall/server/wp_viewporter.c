#include "server/wp_viewporter.h"
#include "server/wl_compositor.h"
#include "server/wp_relative_pointer.h"
#include "config/config.h"
#include "server/server.h"
#include "util/alloc.h"
#include <stdint.h>
#include <wayland-server-core.h>
#include "viewporter-server-protocol.h"

#define SRV_RELATIVE_VIEWPORTER_VERSION 1

static void wp_viewporter_destroy(struct wl_client *client, struct wl_resource *resource) {
    wl_resource_destroy(resource);
}

static void wp_viewporter_get_viewport(struct wl_client *client,
                                     struct wl_resource *viewporter_resource,
                                     uint32_t id,
                                     struct wl_resource *surface_resource) {
    struct server_viewporter *viewporter = wl_resource_get_user_data(viewporter_resource);
    struct server_surface *surface = server_surface_from_resource(surface_resource);
    viewporter->server->backend
}

static struct wp_viewporter_interface viewporter_impl = {
    .destroy = wp_viewporter_destroy,
    .get_viewport = wp_viewporter_get_viewport,
};

static void viewporter_resource_destroy(struct wl_resource *resource) {
    // unused
}

static void on_global_bind(struct wl_client *client, void *data, uint32_t version, uint32_t id) {
    struct server_viewporter *viewporter = data;

    struct wl_resource *resource =
        wl_resource_create(client, &wp_viewporter_interface, version, id);
    check_alloc(resource);
    wl_resource_set_implementation(resource, &viewporter_impl, viewporter,
                                    viewporter_resource_destroy);
}

struct server_viewporter *server_viewporter_create(struct server *server, struct config *cfg) {
    struct server_viewporter *viewporter = zalloc(1, sizeof(*viewporter));
    viewporter->server = server;
    viewporter->global = wl_global_create(server->display, &wp_viewporter_interface,
                         SRV_RELATIVE_VIEWPORTER_VERSION, viewporter, on_global_bind);
    check_alloc(viewporter->global);
    return viewporter;
}
