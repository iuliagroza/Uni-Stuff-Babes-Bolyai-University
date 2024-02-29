import { Container } from "@mui/material";
import { Card, CardContent, IconButton } from "@mui/material";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { BACKEND_URL } from "../../utils";
import { UserProfile } from "../../models/UserProfile";

export const ShowUserProfile = () => {
    const { userId } = useParams();
    const [user, setUser] = useState<any>();

    useEffect(() => {
        const fetchUserProfile = async () => {
            const response = await fetch(`${BACKEND_URL}/users/profile/${userId}`);
            const user = await response.json();
            setUser(user);
        };
        fetchUserProfile();
    }, [userId]);


    return (
        <Container>
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <Container sx={{ display: "flex", flexDirection: "column", justifyContent: "space-evenly", alignContent: "center" }}>
                        <h3> - User profile -</h3>
                        <p>First name: {user?.first_name}</p>
                        <p>Last name: {user?.last_name}</p>
                        <p>Bio: {user?.bio}</p>
                        <p>City: {user?.location}</p>
                        <p>Gender: {user?.gender}</p>
                        <p>Username: {user?.user.username}</p>
                        <p>Email: {user?.user.email}</p>
                        <p style={{ textAlign: "left", marginLeft: "12px" }}>Entities added:</p>
                        <ul>
                            <li>Customers: {user?.entities_added[0]}</li>
                            <li>Accounts: {user?.entities_added[1]}</li>
                        </ul>
                    </Container>

                </CardContent>
            </Card>
        </Container>
    );
}