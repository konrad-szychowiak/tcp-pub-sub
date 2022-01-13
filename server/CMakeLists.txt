cmake_minimum_required(VERSION 3.17)
project(server)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall)
add_link_options(-pthread)

add_executable(server src/main.cpp

        src/socket.cc
        src/server.cc
        src/logger.cc
        src/listeners/ConversationsListener.cpp
                src/ConversationsManager.cpp
                src/Conversation.cpp
                src/Message.cpp

        src/abstract/Listener.cpp
        src/abstract/Notifier.cpp
        src/abstract/visiting.cpp

        src/socket.hh
        src/server.hh
        src/logger.hh
#        src/ConversationsListener.h
#        src/ConversationsManager.h
#        src/Conversation.h
#        src/Message.h
        src/abstract/Notifier.h
        src/abstract/Listener.h
#        src/abstract/Visitable.h
#        src/abstract/Visitor.h


#       src/visitors/ConversationsVisitor.h
#       src/visitors/MessagesVisitor.h


        src/abstract/Observable.cc src/abstract/Observable.hh
        src/mutex.hh)
