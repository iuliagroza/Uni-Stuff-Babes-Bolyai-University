import { Autocomplete, Button, Card, CardActions, CardContent, Container, CssBaseline, FormLabel, IconButton, TextField, colors } from "@mui/material";
import { Link, useNavigate, useParams } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { useEffect, useState } from "react";
import { AccountMenu } from "./AccountMenu";
import { Account } from "../../models/Account";
import React from "react";


export const UpdateAccount = () => {
    const { accountId } = useParams<{ accountId: string }>();
    const navigate = useNavigate();
    const [loading, setLoading] = useState(false);

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

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/account/${accountId}`).then(response => response.json()).then(data => {
            setAccount(data);
            setLoading(false);
        });
    }, [accountId]);

    const updateAccount = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        setLoading(true);
        fetch(`${BACKEND_URL}/account/${accountId}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(account)
        }).then(response => {
            if (response.ok) {
                alert("Account updated successfully.");
            } else {
                console.error('Error updating account:', response.statusText);
                alert("Error updating account: " + response.statusText);
            }
            navigate(`/account`);
            setLoading(false);
        }).catch(error => {
            console.error('Error updating account:', error);
            setLoading(false);
        });
    }

    const handleCancel = (event: { preventDefault: () => void }) => {
        event.preventDefault();
        navigate("/account");
    };

    return (
        <React.Fragment>
            <CssBaseline />

            <AccountMenu />
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/account`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <form onSubmit={updateAccount} style={{ display: "flex", flexDirection: "column", padding: "8px" }}>
                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Name
                            </FormLabel>
                            <TextField
                                id="name"
                                variant="outlined"
                                value={account.name}
                                error={!validName}
                                onChange={handleNameChange}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                IBAN
                            </FormLabel>
                            <TextField
                                id="iban"
                                variant="outlined"
                                onChange={(event) => setAccount({ ...account, iban: event.target.value })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                BIC/SWIFT
                            </FormLabel>
                            <TextField
                                id="bicswift"
                                variant="outlined"
                                onChange={(event) => setAccount({ ...account, bicswift: event.target.value })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Balance
                            </FormLabel>
                            <TextField
                                id="balance"
                                variant="outlined"
                                onChange={(event) => setAccount({ ...account, balance: parseInt(event.target.value) })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Currency
                            </FormLabel>
                            <TextField
                                id="currency"
                                variant="outlined"
                                onChange={(event) => setAccount({ ...account, currency: event.target.value })}
                            />
                        </Container>
                    </form>
                </CardContent>
                <CardActions sx={{ justifyContent: "center" }}>
                    <Button type="submit" onClick={updateAccount} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Update</Button>
                    <Button onClick={handleCancel} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Cancel</Button>
                </CardActions>
            </Card>
        </React.Fragment>
    );
}