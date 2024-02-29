import React from 'react';

export type Message = {
    id: string;
    user: string;
    content: string;
};

export const ChatMessage: React.FC<Message> = ({ user, content }) => (
    <div>
        <strong>{user}</strong>: <span>{content}</span>
    </div>
);