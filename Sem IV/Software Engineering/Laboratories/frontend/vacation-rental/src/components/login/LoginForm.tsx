import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { HomeMenu } from './HomeMenu';
import { Button, CssBaseline, colors } from '@mui/material';

interface User {
    username: string;
    role: string;
}

const LoginForm: React.FC = () => {
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");
    const navigate = useNavigate();

    const handleSubmit = async (e: React.FormEvent) => {
        e.preventDefault();

        try {
            const response = await fetch('http://your-backend-url.com/login', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    username,
                    password,
                }),
            });

            if (!response.ok) {
                throw new Error("Invalid username or password");
            }

            const user = await response.json();

            // Navigate to different routes based on the user role
            if (user.role === 'admin') {
                navigate('/admin');
            } else {
                navigate('/');
            }

        } catch (error) {
            console.error(error);
        }
    };

    const formStyle: React.CSSProperties = {
        display: 'flex',
        flexDirection: 'column',
        width: '300px',
        margin: '0 auto',
    };

    const inputStyle: React.CSSProperties = {
        margin: '10px 0',
        padding: '10px',
        fontSize: '16px',
        width: '100%',
    };

    return (
        <React.Fragment>
            <CssBaseline />

            <HomeMenu />
            <form onSubmit={handleSubmit} style={formStyle}>
                <label>
                    Username:
                    <input
                        type="text"
                        value={username}
                        onChange={e => setUsername(e.target.value)}
                        style={inputStyle}
                        required
                    />
                </label>
                <label>
                    Password:
                    <input
                        type="password"
                        value={password}
                        onChange={e => setPassword(e.target.value)}
                        style={inputStyle}
                        required
                    />
                </label>
                <Button type="submit" variant="contained" sx={{ backgroundColor: colors.pink[500] }}>
                    Submit
                </Button>
            </form>
        </React.Fragment>
    );
};

export default LoginForm;
