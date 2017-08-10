#include "reader.h"

DECLARE_SM(reader, 1234);

static sensor_data SM_FUNC(reader) transform_readings(sensor_data data)
{
    return data ^ 0xcafe;
}

void get_readings(ReaderOutput* out)
{
    sensor_data data = read_sensor_data();
    out->data = transform_readings(data);
    sancus_tag(&out->data, sizeof(out->data), out->mac);

}

