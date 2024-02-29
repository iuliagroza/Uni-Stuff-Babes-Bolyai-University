import React, { useState } from 'react';
import ChatWindow from './ChatWindow';
import { ChatInput } from './ChatInput';
import { Message } from './ChatMessage';

const Chat: React.FC = () => {
    const [messages, setMessages] = useState<Message[]>([]);

    const handleSend = (content: string) => {
        // For simplicity, we'll use the current timestamp as the message ID
        const newMessage: Message = {
            id: Date.now().toString(),
            user: 'User', // Replace this with the actual user
            content,
        };

        setMessages(prevMessages => [...prevMessages, newMessage]);
    };

    return (
        <div>
            <ChatWindow messages={messages} />
            <ChatInput onSend={handleSend} />
        </div>
    );
};

export default Chat;
