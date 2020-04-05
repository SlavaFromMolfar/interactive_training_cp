#ifndef DET_DETECTION_H
#define DET_DETECTION_H


class Detection {
private:
    int ide;  // detection identifier
    float score;  // detection score
    int u1,v1,u2,v2;  // detection location
public:
    Detection();  // constructor
    ~Detection(); // destructor
    void set_u1(int u1);  // set detection values
    void set_v1(int v1);  // set detection values
    void set_u2(int u2);  // set detection values
    void set_v2(int v2);  // set detection values
    void set_score(float score);  // set detection values
    void set_ide(int ide);  // set detection values
    int get_u1();  // return detection values
    int get_v1();  // return detection values
    int get_u2();  // return detection values
    int get_v2();  // return detection values
    float get_score();  // return detection values
    int get_ide();  // return detection values
};


#endif //DET_DETECTION_H
