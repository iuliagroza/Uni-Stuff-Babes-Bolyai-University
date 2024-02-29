import { Link, useNavigate, useParams } from "react-router-dom";
import { useState } from "react";
import { BACKEND_URL } from "../../utils";
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
import { AccountMenu } from "./AccountMenu";
import { Account } from "../../models/Account";
import React from "react";

export const AddAccount = () => {
    const { accountId } = useParams<{ accountId: string }>();
    const navigate = useNavigate();
    const [loading, setLoading] = useState(false);
    const { register, handleSubmit } = useForm<Account>();

    const [account, setAccount] = useState<Account>({
        id: parseInt(String(accountId)),
        name: "",
        iban: "",
        bicswift: "",
        balance: 0,
        currency: "",
    });

    const [validName, setValidName] = useState(true);

    const handleNameChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        const name = event.target.value;
        setAccount({ ...account, name: name });
        setValidName(name.length >= 5);
    };

    const addAccount = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        setLoading(true);
        fetch(`${BACKEND_URL}/account`, {
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
        });
    }

    return (
        <React.Fragment>
            <CssBaseline />

            <AccountMenu />
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/account`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <form onSubmit={addAccount}>
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
                                Name
                            </FormLabel>
                            <TextField
                                {...register("name")}
                                id="name"
                                label="Name"
                                variant="outlined"
                                sx={{ flex: "0 0 70%" }}
                                error={!validName}
                                onChange={handleNameChange}
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
                                IBAN
                            </FormLabel>
                            <TextField
                                {...register("iban")}
                                id="iban"
                                label="IBAN"
                                variant="outlined"
                                sx={{ flex: "0 0 70%" }}
                                onChange={(event) => setAccount({ ...account, iban: event.target.value })}
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
                                BIC/SWIFT
                            </FormLabel>
                            <TextField
                                {...register("bicswift")}
                                id="bicswift"
                                label="BIC/SWIFT"
                                variant="outlined"
                                sx={{ flex: "0 0 70%" }}
                                onChange={(event) => setAccount({ ...account, bicswift: event.target.value })}
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
                                Balance
                            </FormLabel>
                            <TextField
                                {...register("balance")}
                                id="balance"
                                label="Balance"
                                variant="outlined"
                                sx={{ flex: "0 0 70%" }}
                                onChange={(event) => setAccount({ ...account, balance: parseInt(event.target.value) })}
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
                                Currency
                            </FormLabel>
                            <TextField
                                {...register("currency")}
                                id="currency"
                                label="Currency"
                                variant="outlined"
                                sx={{ flex: "0 0 70%" }}
                                onChange={(event) => setAccount({ ...account, currency: event.target.value })}
                            />
                        </Container>

                        <Button type="submit" variant="contained" sx={{ backgroundColor: colors.pink[500] }}>
                            Add account
                        </Button>
                    </form>
                </CardContent>
            </Card>
        </React.Fragment>
    );
};

