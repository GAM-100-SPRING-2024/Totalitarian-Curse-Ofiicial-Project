#include <cprocessing.h>
#include <player.h>
#include <level.h>


// PLAYER
// Handles core player mechanics (walk, run, jump, swim, fight* future implementation)
// Stores player variables (health, position, currentLevel, etc)
// Collision detection from ground and platforms
// Ground collision handled by environment.c 
// Will detect tiles from environment.c and affect movement/health/ability to swim
// Platform collision handled by environment.c
// Initialized by game.c


// STRUCTS 

// Player Struct
typedef struct {
    CP_Vector position;
    CP_Vector velocity;
    int width;
    int height;
    int state; // Used for player states: idle, walking, jumping, crouching, running
    int health;
    int lives;
    int score;
    int currentLevel;
    int lavaTimer;
    int waterTimer;
    int doubleJump; // Track double jump availability
} Player;

// Player State Constants
#define STATE_IDLE 0
#define STATE_WALKING 1
#define STATE_JUMPING 2
#define STATE_CROUCHING 3
#define STATE_RUNNING 4

// Program functions

void player_handle_input(Player* player) {
    // Jumping/Swimming Upward/Crouching/Swimming Downward
    if (CP_Input_KeyTriggered(KEY_W)) {
        if (player->state != STATE_JUMPING && player->state != STATE_CROUCHING && player->doubleJump == 0) {
            // Normal jumping behavior if not already jumping or crouching
            player->velocity.y = -jump_force;
            player->state = STATE_JUMPING;
        }
        else if (player->doubleJump == 1) {
            // Double jump
            player->velocity.y = -jump_force;
            player->doubleJump = 0;
        }
    }
    else if (CP_Input_KeyPressed(KEY_S)) {
        if (player->state != STATE_JUMPING && player->state != STATE_CROUCHING) {
            // Crouching behavior if not already jumping or crouching
            player->state = STATE_CROUCHING;
            // Adjust player's height when crouching
            player->height /= 2;
            // Slow down player's speed while crouching
            move_speed = 2;
        }
    }
    else {
        if (player->state == STATE_CROUCHING) {
            // Reset player's height when not crouching
            player->height *= 2;
            player->state = STATE_IDLE;
            // Restore normal player speed
            move_speed = 4;
        }
    }

    // Swimming/Running mechanics
    if (CP_Input_KeyDown(KEY_A)) {
        if (player->state != STATE_JUMPING && player->state != STATE_CROUCHING) {
            player->velocity.x = -move_speed;
            if (CP_Input_KeyDown(KEY_A) && player->state != STATE_RUNNING) {
                player->state = STATE_RUNNING;
            }
        }
    }
    else if (CP_Input_KeyDown(KEY_D)) {
        if (player->state != STATE_JUMPING && player->state != STATE_CROUCHING) {
            player->velocity.x = move_speed;
            if (CP_Input_KeyDown(KEY_D) && player->state != STATE_RUNNING) {
                player->state = STATE_RUNNING;
            }
        }
    }
    else {
        if (player->state == STATE_RUNNING) {
            player->state = STATE_IDLE; // Player is not running
        }
        // Player is not moving horizontally
        player->velocity.x = 0;
    }
}

void player_check_collisions(Player* player, TileInfo* tiles, int gridCols) {
    int playerTileX = (int)(player->position.x / tileWidth);    // Calculate player's tile X position
    int playerTileY = (int)(player->position.y / tileHeight);   // Calculate player's tile Y position

    // Check if player is within the game boundaries
    if (playerTileX >= 0 && playerTileX < gridCols && playerTileY >= 0 && playerTileY < gridRows) {
        TileInfo currentTile = tiles[playerTileY * gridCols + playerTileX]; // Get properties of the current tile

        // Collision with block
        if (currentTile.viscosity == 0) {
            // Prevent player from entering the block's X and Y values
            player->position.x -= player->velocity.x;
            player->position.y -= player->velocity.y;

            // Stop player's X velocity
            player->velocity.x = 0;

            // If the player tries to jump into a block, stop the jump
            if (player->state == STATE_JUMPING) {
                player->velocity.y = 0;
            }
        }

        // Friction based movement
        switch (currentTile.friction) {
        case 1: // High friction (slower movement)
            move_speed = 2;
            break;
        case 2: // Medium friction
            move_speed = 4;
            break;
        case 3: // Low friction (faster movement)
            move_speed = 6;
            break;
        default:
            break;
        }

        // Update player's state based on the viscosity of the current tile
        switch (currentTile.viscosity) {
        case 1: // Player can go through a block very slowly (lava)
            if (player->state == inLava) {
                player->velocity.x *= lava_speed_multiplier;
                player->velocity.y *= lava_gravity_multiplier;
            }
            break;
        case 2: // Player can go through a block at medium pace (water)
            if (player->state == inWater) {
                player->velocity.x *= water_speed_multiplier;
                player->velocity.y *= water_gravity_multiplier;
            }
            break;
        default:
            // No special viscosity associated with the current tile
            break;
        }
    }
}


void player_update(Player* player) {
    // Apply gravity if player is not jumping
    if (player->state != STATE_JUMPING) {
        player->velocity.y += gravity;
    }

    // Update player position based on velocity
    player->position = CP_Vector_Add(player->position, player->velocity);

    // Handle screen collision
    player_screen_collision(player);

    // Handle collisions with the environment
    player_check_collisions(player);

    // Respawn player if they fall below the world
    if (player->position.y > screenHeight) {
        player_respawn(player);
    }
}

void player_screen_collision(Player* player) {
    // Check if player collides with screen boundaries for room transitions
    if (player->position.x + player->width / 2 > screenWidth) {
        // Player is colliding with the right side of the screen
        // Implement room transition logic here
    }
    else if (player->position.x - player->width / 2 < 0) {
        // Player is colliding with the left side of the screen
        // Implement room transition logic here
    }
}

void player_respawn(Player* player) {
    // Respawn player at tile (3, 21) and decrement life count
    player->position.x = 3 * tileWidth;
    player->position.y = 21 * tileHeight;
    player->lives--;
    player->health = 100;

    // Check if player has lost all lives
    if (player->lives <= 0) {
        // Implement game over logic here
    }
}

void player_timer(Player* player, float dt) {
    // Update player timers based on state
    if (player->state == STATE_JUMPING) {
        // Increment lava timer if player is in lava
        if (player->inLava) {
            player->lavaTimer += dt;
        }
        // Increment water timer if player is in water
        else if (player->inWater) {
            player->waterTimer += dt;
        }
    }
    else {
        // Reset timers if player is not jumping
        player->lavaTimer = 0;
        player->waterTimer = 0;
    }
}





/*

#define jump_speed_initial -700.0f
#define gravity_initial 9.8f * 20.0f
#define max_jump_height 300.0f
#define jump_decay_factor 0.5f

Character Player;

extern float gravity;

void spawnPlayer(float spawnX, float spawnY) {
    Player.posX = spawnX;
    Player.posY = spawnY;
    Player.radius = 20.0f; // Adjust as needed
    Player.isJumping = 0;
    Player.groundHeight = 0.0f;
    Player.jumpSpeed = 0.0f;
    Player.jumpElapsedTime = 0.0f;
    Player.jumpTime = 0.0f;
    Player.CharColor = CP_Color_Create(255, 0, 0, 255); // Red color for player
}

void updateJump(float dt) {
    if (Player.isJumping) {
        Player.jumpSpeed += gravity * dt;

        if (Player.jumpSpeed >= 0) {
            Player.jumpSpeed *= jump_decay_factor;
        }

        Player.posY += Player.jumpSpeed * dt;

        if (Player.posY >= Player.groundHeight) {
            Player.posY = Player.groundHeight;
            Player.isJumping = 0;
            Player.jumpSpeed = 0;
        }
    }
}

void jump() {
    if (!Player.isJumping) {
        Player.isJumping = 1;
        Player.jumpSpeed = jump_speed_initial;
        Player.groundHeight = Player.posY;
    }
}

void move(int stop) {
    // Movement logic for left and right
    // Implement according to your requirements
    float movementSpeed = 200.0f; // Adjust as needed
    if (stop != 2) {
        if (CP_Input_KeyDown(KEY_A)) {
            Player.posX -= movementSpeed * CP_System_GetDt();
        }
    }
    if (stop != 1) {
        if (CP_Input_KeyDown(KEY_D)) {
            Player.posX += movementSpeed * CP_System_GetDt();
        }
    }
}

int hitGround(GroundData grounds[])
{
    for (int i = 0; i < GroundCount; i++) {
        if (Player.posX < grounds[i].posX + grounds[i].width &&
            Player.posX + Player.radius > grounds[i].posX &&
            Player.posY < grounds[i].posY + grounds[i].height &&
            Player.posY + Player.radius > grounds[i].posY)
        {
            return 1;
        }
    }
    return 0;
}

int hitWall(GroundData walls[])
{
    for (int i = 0; i < wallCount; i++) {
        if (Player.posX < walls[i].posX + walls[i].width &&
            Player.posX + Player.radius > walls[i].posX &&
            Player.posY < walls[i].posY + walls[i].height &&
            Player.posY + Player.radius > walls[i].posY)
        {
            return 1;
        }
    }
    return 0;
}

void airMove(int stop) {
    // Air movement logic
    float movementSpeed = 350.0f; // Adjust as needed
    if (stop != 2) {
        if (CP_Input_KeyDown(KEY_A)) {
            Player.posX -= movementSpeed * CP_System_GetDt();
        }
    }
    if (stop != 1) {
        if (CP_Input_KeyDown(KEY_D)) {
            Player.posX += movementSpeed * CP_System_GetDt();
        }
    }
    if (stop == 4) {
        Player.isJumping = 0;
        Player.jumpElapsedTime = 0;
    }
}

void CharacterMovement(GroundData grounds[], GroundData walls[]) {
    float jumpSpeed = 800.0f; // Adjust as needed

    if (hitGround(grounds) == 0 && hitWall(walls) != 3 && Player.isJumping == 0) {
        gravity = gravity_initial;
        airMove(hitWall(walls));
    }
    else if (hitGround(grounds) == 1 || hitWall(walls) != 0) {
        gravity = 0.0f;
        airMove(hitWall(walls));

        if (CP_Input_KeyTriggered(KEY_W) && hitWall(walls) != 0) {
            Player.isJumping = 1;
        }
        else if (CP_Input_KeyTriggered(KEY_W) && hitGround(grounds) == 1) {
            Player.isJumping = 1;
        }
        else {
            Player.isJumping = 0;
        }

    }
    else {
        gravity = 0;
        airMove(0);
    }

    if (Player.isJumping == 1) {
        Player.jumpTime = 0.3f;
        if (Player.jumpElapsedTime < Player.jumpTime) {
            Player.jumpElapsedTime += 1.0f * CP_System_GetDt();
            Player.posY -= jumpSpeed * CP_System_GetDt();
        }
        else {
            Player.jumpElapsedTime = 0;
            Player.isJumping = 0;
        }

    }

    Player.posY += gravity * CP_System_GetDt();
    CP_Settings_Fill(Player.CharColor);
    CP_Graphics_DrawCircle(Player.posX, Player.posY, Player.radius);
}

*/