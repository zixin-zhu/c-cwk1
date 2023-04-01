#ifndef PGM_STRUCT_DEFINED
typedef struct _pgm {
  /*format is R for raw or P for plain  **/
  unsigned char format;
  /**comment line*/ 
  char * commentLine;
  /*width and height**/
  unsigned int width, height;  
  /*max gray value**/
  unsigned int maxGray;
  /*image data**/
  unsigned char ** imageData;
} PGM;
#define PGM_STRUCT_DEFINED 1
#endif
