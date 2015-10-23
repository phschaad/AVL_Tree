# README #

This is a very basic implementation of an AVL-Tree in C, by Philipp Schaad. The implementation is done in a modular style, allowing quick and easy integration of the AVL-Tree in to any type of program.

### In Short: ###

* This is a very basic implementation of an AVL-Tree in C. Modular design allows quick and easy integration in any C/C++ project.
* Current Version: 1.0.0

### How do I get set up? ###

* If you want to use the AVL-Tree Module, you need to copy the avl_core.c and avl_core.h files in to your project folder, and include avl_core.h.
* The core-module itself does not contain a main method. If you need one, you will have to supply one yourself. Alternatively you can copy the test-avl.c file in to you project, which contains a main method. The method simply tests the AVL-Tree.
* In addition to the core module there is a visualizion module (avl_visualizer.c / avl_visualizer.h). The integration in to the project follows the same rules as the core module.
* Dependencies: 
    - avl_core:
        * Non-Standard: avl_core.h (supplied)
        * Standard: stdio.h, stdlib.h (and pre-deployment: assert.h)
    - avl_visualizer:
        * Non-Standard: avl_core.h (supplied), avl_visualizer.h (supplied)
        * Standard: stdio.h, stdlib.h, math.h (and pre-deployment: assert.h)
    - test-avl.c:
        * Non-Standard: avl_core.h (supplied), avl_visualizer.h (supplied)
        * Standard: stdio.h, stdlib.h, time.h, math.h (and pre-deployment: assert.h)
* To run tests just disable your standard main method (if you have one), and include the test-avl.c to your compilation. You may modify the main method however you like, to test the AVL-Tree to your liking.

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Contact ###

* Project Admin and Author: [Philipp Schaad](mailto:philipp@schaadfamily.com)