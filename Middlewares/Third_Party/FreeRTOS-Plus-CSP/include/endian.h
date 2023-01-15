/*
 * endian.h
 *
 *  Created on: Jan 08, 2023
 *      Author: roy.ratcliffe
 */

#ifndef INC_ENDIAN_H_
#define INC_ENDIAN_H_

#include <machine/endian.h>

#if _BYTE_ORDER == _LITTLE_ENDIAN
#define htobe16(x) __bswap16(x)
#define htobe32(x) __bswap32(x)
#define htobe64(x) __bswap64(x)
#define be16toh(x) __bswap16(x)
#define be32toh(x) __bswap32(x)
#define be64toh(x) __bswap64(x)
#else
#define htobe16(x) (x)
#define htobe32(x) (x)
#define htobe64(x) (x)
#define be16toh(x) (x)
#define be32toh(x) (x)
#define be64toh(x) (x)
#endif

#endif /* INC_ENDIAN_H_ */
