import { Link, useNavigate, useParams } from "react-router-dom";
import { useState } from "react";
import {
    Button,
    Card,
    CardContent,
    Container,
    IconButton,
    TextField,
    FormLabel,
    colors,
    CssBaseline
} from "@mui/material";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { useForm } from "react-hook-form";
import { UserMenu } from "./UserMenu";
import React from "react";
import { Destination } from "../../models/Destination";

export const AddPrivateDestination = () => {
    const { destinationId } = useParams<{ destinationId: string }>();
    const navigate = useNavigate();
    const [loading, setLoading] = useState(false);
    const { register, handleSubmit } = useForm<Destination>();

    const [destination, setDestination] = useState<Destination>({
        id: parseInt(String(destinationId)),
        geolocation: "",
        title: "",
        image: "",
        description: "",
        stay_dates: "",
    });

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
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/admin`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
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
                                Geolocation
                            </FormLabel>
                            <TextField
                                {...register("geolocation")}
                                id="geolocation"
                                label="Geolocation"
                                variant="outlined"
                                sx={{ flex: "0 0 70%" }}
                            />
                        </Container>

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
                                Title
                            </FormLabel>
                            <TextField
                                {...register("title")}
                                id="title"
                                label="Title"
                                variant="outlined"
                                sx={{ flex: "0 0 70%" }}
                                onChange={(event) => setDestination({ ...destination, title: event.target.value })}
                            />
                        </Container>

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
                                Image
                            </FormLabel>
                            <TextField
                                {...register("image")}
                                id="image"
                                label="Image"
                                variant="outlined"
                                sx={{ flex: "0 0 70%" }}
                                onChange={(event) => setDestination({ ...destination, image: event.target.value })}
                            />
                        </Container>

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
                                Description
                            </FormLabel>
                            <TextField
                                {...register("description")}
                                id="description"
                                label="Description"
                                variant="outlined"
                                sx={{ flex: "0 0 70%" }}
                                onChange={(event) => setDestination({ ...destination, description: event.target.value })}
                            />
                        </Container>

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
}
