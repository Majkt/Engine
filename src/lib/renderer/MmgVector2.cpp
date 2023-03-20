#include "MmgVector2.h"

namespace majkt {

    MmgVector2::MmgVector2(std::array<double, 2> &vec) {
        mVec = vec;
    }

    MmgVector2::MmgVector2() {
        mVec = {static_cast<double>(0), static_cast<double>(0)};
    }

    MmgVector2::MmgVector2(MmgVector2 &vec) {
        mVec = vec.GetVector();
    }

    MmgVector2::MmgVector2(int x, int y) {
        mVec = {static_cast<double>(x), static_cast<double>(y)};
        mType = 'i';
    }

    MmgVector2::MmgVector2(float x, float y) {
        mVec = {static_cast<double>(x), static_cast<double>(y)};
        mType = 'f';
    }

    MmgVector2::MmgVector2(double x, double y) {
        mVec = {static_cast<double>(x), static_cast<double>(y)};
    }

    MmgVector2 MmgVector2::Clone(){
        if(this->mType == 'i'){
            return CloneInt();
        } else if(this->mType == 'f'){
            return CloneFloat();
        } else {
            return CloneDouble();
        }
    }

    MmgVector2 MmgVector2::CloneInt(){
        return MmgVector2(GetX(), GetY());
    }

    MmgVector2 MmgVector2::CloneFloat(){
        return MmgVector2(GetXFloat(), GetYFloat());
    }

    MmgVector2 MmgVector2::CloneDouble(){
        return MmgVector2(GetXDouble(), GetYDouble());
    }

    MmgVector2 MmgVector2::GetOriginVec() {
        return MmgVector2();
    }

    MmgVector2 MmgVector2::GetUnitVec() {
        return MmgVector2(1, 1);
    }

    std::array<double, 2> MmgVector2::GetVector() {
        return mVec;
    }

    void MmgVector2::SetVector(std::array<double, 2> &vec) {
        mVec = vec;
    }

    int MmgVector2::GetX() {
        return static_cast<int>(mVec[0]);
    }
    int MmgVector2::GetY() {
        return static_cast<int>(mVec[1]);
    }

    float MmgVector2::GetXFloat() {
        return static_cast<float>(mVec[0]);
    }
    float MmgVector2::GetYFloat() {
        return static_cast<float>(mVec[1]);
    }
    double MmgVector2::GetXDouble() {
        return mVec[0];
    }
    double MmgVector2::GetYDouble() {
        return mVec[1];
    }
    void MmgVector2::SetX(int &x) {
        mVec[0] = static_cast<double>(x);
    }
    void MmgVector2::SetY(int &y) {
        mVec[1] = static_cast<double>(y);
    }
    void MmgVector2::SetX(float &x) {
        mVec[0] = static_cast<double>(x);
    }
    void MmgVector2::SetY(float &y) {
        mVec[1] = static_cast<double>(y);
    }
    void MmgVector2::SetX(double &x) {
        mVec[0] = x;
    }
    void MmgVector2::SetY(double &y) {
        mVec[1] = y;
    }

    std::string MmgVector2::ApiToString() {
        std::string ret = "MmgVector2: X: " + std::to_string(GetX()) + " Y: " + std::to_string(GetY());
        return ret;
    }

    bool MmgVector2::ApiEquals(MmgVector2 *obj) {
        bool ret = false;
        if (obj == nullptr) {
            return ret;
        } else if(obj->mType == 'i'){
            if(this->mType == 'i'){
                if (obj->GetX() == GetX() && obj->GetY() == GetY()) {
                    ret = true;
                }
            } else if(this->mType == 'f'){
                if (obj->GetXFloat() == GetXFloat() && obj->GetYFloat() == GetYFloat()) {
                    ret = true;
                }
            } else {
                if (obj->GetXDouble() == GetXDouble() && obj->GetYDouble() == GetYDouble()) {
                    ret = true;
                }
            }
        }
        return ret; 
    }
}