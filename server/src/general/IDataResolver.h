#ifndef IDATARESOLVER_H
#define IDATARESOLVER_H

#include <string>
#include <boost/system/error_code.hpp>

class IDataResolver {
public:
    virtual void resolve(std::string data) = 0;
    virtual void resolve_error(const boost::system::error_code& error) = 0;
};

#endif //IDATARESOLVER_H
