#pragma once

#include <string>
#include <vector>
#include <memory>

class Domain;

class Base_IO
{
public:
    virtual void Write() = 0;
    virtual void Read() = 0;
    Base_IO(const Domain& domain);

protected:
    uint output_id{};
    const Domain& domain;
};

class csv_IO : public Base_IO
{
public:
    csv_IO(const Domain& domain);

    void Write() override;
    // TODO
    void Read() override {};
};
