import React from 'react';
import { ChatMessage, Message } from './ChatMessage';

type ChatWindowProps = {
    messages: Message[];
};

const ChatWindow: React.FC<ChatWindowProps> = ({ messages }) => (
    <div>
        {messages.map(message => (
            <ChatMessage key={message.id} {...message} />
        ))}
    </div>
);

export default ChatWindow;
