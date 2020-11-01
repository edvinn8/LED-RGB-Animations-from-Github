// ***************************************************************************
// DEFINE: Animation driver
// ***************************************************************************     
      //#define USE_NEOANIMATIONFX  // Uses NeoAnimationFX, PIN is ignored & set to RX/GPIO3 or UART method: D4/GPIO2, see: https://github.com/debsahu/NeoAnimationFX
      #define USE_WS2812FX          // Uses WS2812FX, see: https://github.com/kitesurfer1404/WS2812FX

// ***************************************************************************
// DEFINE: Pins
// ***************************************************************************  
      #define PIN 6              // PIN (15 / D8) where neopixel / WS2811 strip is attached 
      #define NUMLEDS 61        // Number of leds in the strip 

// ***************************************************************************
// DEFINE: LED Type
// ***************************************************************************  
      #define RGBW               // If defined, use RGBW Strips
      
// ***************************************************************************
// DEFINE: other Options
// ***************************************************************************  
      #define ENABLE_LEGACY_ANIMATIONS
      #define REDUCED_MODES
// ***************************************************************************
// DEFINE: Alias
// ***************************************************************************   
      #define DBG_OUTPUT_PORT Serial  // Set debug output port


// ***************************************************************************
// Global variables / definitions
// ***************************************************************************

      // List of all color modes
      #ifdef ENABLE_LEGACY_ANIMATIONS
            enum MODE { SET_MODE, HOLD, AUTO, OFF, TV, CUSTOM, SETCOLOR, SETSPEED, BRIGHTNESS, WIPE, RAINBOW, RAINBOWCYCLE, THEATERCHASE, TWINKLERANDOM, THEATERCHASERAINBOW};
            MODE mode = RAINBOW;         // Standard mode that is active when software starts
            bool exit_func = false;      // Global helper variable to get out of the color modes when mode changes
      #else
            enum MODE { SET_MODE, HOLD, AUTO, OFF, TV, CUSTOM, SETCOLOR, SETSPEED, BRIGHTNESS};
            MODE mode = SET_MODE;        // Standard mode that is active when software starts
      #endif

      void checkForNewCommands();
      boolean newData = false;
      MODE prevmode = mode;
        
        // ***************************************************************************
        // DEFINE: Default properties
        // ***************************************************************************
            int ws2812fx_speed = 196;   // Global variable for storing the delay between color changes --> smaller == faster
            int brightness = 20;       // Global variable for storing the brightness (255 == 100%)
            int ws2812fx_mode = 0;      // Helper variable to set WS2812FX modes
          
     

        // ***************************************************************************
        // DEFINE: Datatype LED STATE
        // ***************************************************************************
            struct ledstate             // Data structure to store a state of a single led
            {
              uint8_t red;
              uint8_t green;
              uint8_t blue;
              uint8_t white;
            };
          typedef struct ledstate LEDState;     // Define the datatype LEDState

         
        // ***************************************************************************
        // DEFINE: LED STATE for entire LED-Strip
        // *************************************************************************** 
            LEDState ledstates[NUMLEDS];          // Get an array of led states to store the state of the whole strip
            LEDState main_color = { 0, 0, 0, 255};  // Store the "main color" of the strip used in single color modes
            