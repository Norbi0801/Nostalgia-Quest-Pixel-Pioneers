//
// Created by Norbert Olkowski on 12.12.2023.
//

#pragma once

using MessageType = unsigned int;
struct TwoFloats {
    float m_x;
    float m_y;
};

struct Message {
    Message(const MessageType &l_type) : m_type(l_type) {}

    MessageType m_type;
    int m_sender;
    int m_receiver;
    union {
        TwoFloats m_2f;
        bool m_bool;
        int m_int;
    };
};

class Observer {
public:
    virtual ~Observer() {}

    virtual void Notify(const Message &l_message) = 0;
};