// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*! 
 * @file halloPubSubTypes.h
 * This header file contains the declaration of the serialization functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#ifndef _HALLO_PUBSUBTYPES_H_
#define _HALLO_PUBSUBTYPES_H_

#include <fastrtps/TopicDataType.h>

using namespace eprosima::fastrtps;

#include "hallo.h"

namespace airvision
{
    namespace contracts
    {
        /*!
         * @brief This class represents the TopicDataType of the type point_cloud_response defined by the user in the IDL file.
         * @ingroup HALLO
         */
        class point_cloud_responsePubSubType : public TopicDataType {
        public:
                typedef point_cloud_response type;

        	point_cloud_responsePubSubType();
        	virtual ~point_cloud_responsePubSubType();
        	bool serialize(void *data, SerializedPayload_t *payload);
        	bool deserialize(SerializedPayload_t *payload, void *data);
                std::function<uint32_t()> getSerializedSizeProvider(void* data);
        	bool getKey(void *data, InstanceHandle_t *ihandle);
        	void* createData();
        	void deleteData(void * data);
        	MD5 m_md5;
        	unsigned char* m_keyBuffer;
        };
        /*!
         * @brief This class represents the TopicDataType of the type point_cloud_request defined by the user in the IDL file.
         * @ingroup HALLO
         */
        class point_cloud_requestPubSubType : public TopicDataType {
        public:
                typedef point_cloud_request type;

        	point_cloud_requestPubSubType();
        	virtual ~point_cloud_requestPubSubType();
        	bool serialize(void *data, SerializedPayload_t *payload);
        	bool deserialize(SerializedPayload_t *payload, void *data);
                std::function<uint32_t()> getSerializedSizeProvider(void* data);
        	bool getKey(void *data, InstanceHandle_t *ihandle);
        	void* createData();
        	void deleteData(void * data);
        	MD5 m_md5;
        	unsigned char* m_keyBuffer;
        };
    }
}

#endif // _hallo_PUBSUBTYPE_H_