bool F(bool a, bool b) {
    if(a == true){
        if(b == true)
            return true;
        else
            return false;
        return false;
    
}
bool boolAnd(bool a, bool b) {
    return F(a , b);
}
bool boolNot(bool a) {
    if(F(a , a))
        return false;
    else
        return true;
}