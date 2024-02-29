import { Button, Card, CardContent, CssBaseline, FormLabel, IconButton, TextField, colors } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useNavigate, useParams } from "react-router-dom";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { UserMenu } from "./UserMenu";
import { Destination } from "../../models/Destination";
import React from "react";
import { useForm } from "react-hook-form";

export const AddPublicDestination = () => {
    const { destinationId } = useParams();
    const [loading, setLoading] = useState(false);
    const { register, handleSubmit } = useForm<Destination>();
    const navigate = useNavigate();
    const [destination, setDestination] = useState<Destination>({
        id: parseInt(String(destinationId)),
        geolocation: "",
        title: "",
        image: "",
        description: "",
        stay_dates: "",
    });

    useEffect(() => {
        const fetchDestination = async () => {
            /*const response = await fetch(`${BACKEND_URL}/account/${accountId}`);
            const destination = await response.json();
            setDestination(destination[0]);*/
        };
        fetchDestination();
    }, [destinationId]);

    const addDestination = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        setLoading(true);
        /*fetch(`${BACKEND_URL}/account`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(account)
        }).then(response => {
            if (response.ok) {
                alert("Account added successfully");
            } else {
                console.error('Error adding account:', response.statusText);
                alert("Error adding account: " + response.statusText);
            }
            navigate(`/account`);
            setLoading(false);
        }).catch(error => {
            console.error('Error adding account:', error);
            setLoading(false);
        });*/
    }

    return (
        <React.Fragment>
            <CssBaseline />

            <UserMenu />
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <h3>Add Public Destination</h3>
                    <p>Geolocation: {destination?.geolocation}</p>
                    <p>Title: {destination?.title}</p>
                    <p>Image: {destination?.image}</p>
                    <p>Description: {destination?.description}</p>
                    <form onSubmit={addDestination}>
                        <Container
                            sx={{
                                display: "flex",
                                flexDirection: "row",
                                justifyContent: "space-between",
                                alignItems: "center",
                                padding: "3px",
                                width: "100%"
                            }}
                        >
                            <FormLabel
                                sx={{
                                    marginTop: "15px",
                                    fontSize: "18px",
                                    flex: "0 0 30%"
                                }}
                            >
                                Stay Dates
                            </FormLabel>
                            <TextField
                                {...register("stay_dates")}
                                id="stay_dates"
                                label="Stay Dates"
                                variant="outlined"
                                sx={{ flex: "0 0 70%" }}
                                onChange={(event) => setDestination({ ...destination, stay_dates: event.target.value })}
                            />
                        </Container>

                        <Button type="submit" variant="contained" sx={{
                            backgroundColor: colors.pink[500],
                            display: 'block',
                            marginLeft: 'auto',
                            marginRight: 'auto',
                            marginTop: '15px'
                        }}>
                            Add destination
                        </Button>
                    </form>
                </CardContent>
            </Card>
        </React.Fragment>
    );
};


