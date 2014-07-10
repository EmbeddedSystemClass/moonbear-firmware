#include <stddef.h>
#include <stdbool.h>
#include "global.h"
#include "attitude_stabilizer.h"

global_data_t global_mav_data_list[GLOBAL_DATA_CNT];
int modifiable_data_cnt = 0;

#define QUADCOPTER 0

void init_global_data(void)
{
	/* global data information */
	reset_global_data(VEHICLE_TYPE, "vehicle_type", READ_ONLY);
	set_global_data_int(VEHICLE_TYPE, QUADCOPTER);

	/* Boot time */
	reset_global_data(BOOT_TIME, "boot_time", READ_ONLY);
	set_global_data_int(BOOT_TIME, 0);

	/* IMU information */
	reset_global_data(TRUE_ROLL, "imu.roll", READ_ONLY);
	reset_global_data(TRUE_PITCH, "imu.pitch", READ_ONLY);
	reset_global_data(TRUE_YAW, "imu.yaw", READ_ONLY);

        /* GPS Location */
	reset_global_data(GPS_LAT, "gps.latitude", READ_ONLY);
	reset_global_data(GPS_LON, "gps.longitude", READ_ONLY);
	reset_global_data(GPS_ALT, "gps.altitude", READ_ONLY);

	/* GPS Speed */
	reset_global_data(GPS_VX, "gps.vx", READ_ONLY);
	reset_global_data(GPS_VY, "gps.vy", READ_ONLY);
	reset_global_data(GPS_VZ, "gps.vz", READ_ONLY);
} 


/**
  * @brief  reset data value and set global data's name and assess right
  * @param  index (int), name (char *), assess_right (AcessRight)
  * @retval Operated result (0 - succeeded, 1 - error)
  */
int reset_global_data(int index, char *name, AccessRight access_right)
{
	/* Index is in the range or not */
	if((index < 0) || (index >= GLOBAL_DATA_CNT))
		return GLOBAL_SUCCESS;;

	/* Available access right or not */
	if((access_right != READ_ONLY) && (access_right != READ_WRITE))
		return GLOBAL_ERROR_INDEX_OUT_RANGE;

	/* Reset all data to be defalut */
	global_mav_data_list[index].name = name;
	global_mav_data_list[index].type = FLOAT;
	global_mav_data_list[index].flt_value = 0.0;
	global_mav_data_list[index].int_value = 0;
	global_mav_data_list[index].access_right = access_right;
	if(access_right == READ_WRITE) modifiable_data_cnt++;

	return GLOBAL_SUCCESS;
}

/**
  * @brief  get the count of global data
  * @param  None
  * @retval global data count (int)
  */
int get_global_data_count(void)
{
	return GLOBAL_DATA_CNT;
}

/**
  * @brief  get the count of modifiable global data
  * @param  None
  * @retval modifiable global data count (int)
  */
int get_modifiable_data_count(void)
{
	return modifiable_data_cnt;
}

/**
  * @brief  set global data's value (int version)
  * @param  index (int), value (int)
  * @retval Operated result (0 - succeeded, 1 - error)
  */
int set_global_data_int(int index, int value)
{
	/* Index is in the range or not */
	if((index < 0) || (index >= GLOBAL_DATA_CNT))
		return GLOBAL_ERROR_INDEX_OUT_RANGE;

	/* Set the variable type and value */
	global_mav_data_list[index].type = INTEGER;
	global_mav_data_list[index].int_value = value;

	return GLOBAL_SUCCESS;
}

/**
  * @brief  set global data's value (float version)
  * @param  index (int), value (int)
  * @retval Operated result (0 - succeeded, 1 - error)
  */
int set_global_data_float(int index, float value)
{
	/* Index is in the range or not */
	if((index < 0) || (index >= GLOBAL_DATA_CNT))
		return GLOBAL_ERROR_INDEX_OUT_RANGE;

	/* Set the variable type and value */
	global_mav_data_list[index].type = FLOAT;
	global_mav_data_list[index].flt_value = value;	

	return GLOBAL_SUCCESS;
}

/**
  * @brief  get the variable type of global data
  * @param  index (int), variable type (Type* to get the type)
  * @retval Operated result (0 - succeeded, 1 - error)
  */
int get_global_data_type(int index, Type *type)
{
	/* Index is in the range or not */
	if((index < 0) || (index >= GLOBAL_DATA_CNT))
		return GLOBAL_ERROR_INDEX_OUT_RANGE;

	*type = global_mav_data_list[index].type;

	return GLOBAL_SUCCESS;
}

/**
  * @brief  get the access right of global data
  * @param  index (int), access right (AccessRight* to get the type)
  * @retval Operated result (0 - succeeded, 1 - error)
  */
int get_global_data_access_right(int index, AccessRight *access_right)
{
	/* Index is in the range or not */
	if((index < 0) || (index >= GLOBAL_DATA_CNT))
		return GLOBAL_ERROR_INDEX_OUT_RANGE;

	*access_right = global_mav_data_list[index].access_right;

	return GLOBAL_SUCCESS;
}

/**
  * @brief  get the name of global data
  * @param  index (int), name (char* to get the name)
  * @retval Operated result (0 - succeeded, 1 - error)
  */
int read_global_data_name(int index, char **name)
{
        /* Index is in the range or not */
	if((index < 0) || (index >= GLOBAL_DATA_CNT))
		return GLOBAL_ERROR_INDEX_OUT_RANGE;
	
	*name = global_mav_data_list[index].name;

	return GLOBAL_SUCCESS;
}

/**
  * @brief  get the value of global data (int version)
  * @param  index (int), value (int* to get the result value)
  * @retval Operated result (0 - succeeded, 1 - error)
  */
int read_global_data_int(int index, int *value)
{
        /* Index is in the range or not */
	if((index < 0) || (index >= GLOBAL_DATA_CNT))
		return GLOBAL_ERROR_INDEX_OUT_RANGE;
	
	*value = global_mav_data_list[index].int_value;

	return GLOBAL_SUCCESS;
}

/**
  * @brief  get the value of global data (float version)
  * @param  index (float), value (float* to get the result value)
  * @retval Operated result (0 - succeeded, 1 - error)
  */
int read_global_data_float(int index, float *value)
{
        /* Index is in the range or not */
	if((index < 0) || (index >= GLOBAL_DATA_CNT))
		return GLOBAL_ERROR_INDEX_OUT_RANGE;

	*value = global_mav_data_list[index].flt_value;

	return GLOBAL_SUCCESS;
}

/**
  * @brief  get the boot time value
  * @param  None
  * @retval boot time value (int)
  */
uint32_t get_boot_time(void)
{
	uint32_t boot_time;
	read_global_data_int(BOOT_TIME, &boot_time);

	return boot_time;
}

