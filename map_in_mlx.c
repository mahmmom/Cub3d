#include <mlx.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 20 // Size of each tile on the minimap

// Example map data (just a 2D array)
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void draw_minimap(void *mlx_ptr, void *win_ptr) {
    int x, y;
    int player_x = 3; // Example player position
    int player_y = 4;

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            // Calculate positions on the minimap window
            int draw_x = x * TILE_SIZE;
            int draw_y = y * TILE_SIZE;

            // Draw map element
            int color = (map[y][x] == 1) ? 0xFFFFFF : 0x000000; // Wall or empty space
            mlx_pixel_put(mlx_ptr, win_ptr, draw_x, draw_y, color);
        }
    }

    // Draw player position
    int player_draw_x = player_x * TILE_SIZE;
    int player_draw_y = player_y * TILE_SIZE;
    mlx_pixel_put(mlx_ptr, win_ptr, player_draw_x, player_draw_y, 0xFF0000); // Player color: Red
}

int main() {
    void *mlx_ptr;
    void *win_ptr;

    // Initialize MiniLibX
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "Minimap");

    // Draw the minimap
    draw_minimap(mlx_ptr, win_ptr);

    mlx_loop(mlx_ptr); // Start the event loop

    return 0;
}
