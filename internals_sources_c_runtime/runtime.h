#define INITIALIZE_CLASS(initializer) static __attribute__((section(".classInitializers"))) void (*onInit_ ## initializer)() = initializer;