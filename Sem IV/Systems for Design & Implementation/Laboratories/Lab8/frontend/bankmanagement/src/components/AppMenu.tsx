import React, { useState } from "react";
import { AppBar, Box, Button, Divider, Drawer, IconButton, ListItemButton, ListItemText, Toolbar, Typography, colors } from "@mui/material";
import { Link, useLocation } from "react-router-dom";
import LocalLibraryIcon from "@mui/icons-material/LocalLibrary";
import AddIcon from '@mui/icons-material/Add';
import HomeIcon from '@mui/icons-material/Home';
import { useMediaQuery } from 'react-responsive';
import MenuIcon from "@mui/icons-material/Menu";
import CloseIcon from "@mui/icons-material/Close";
import Chat from "./chat/Chat";


export const AppMenu = () => {
    const location = useLocation();
    const path = location.pathname;
    const [open, setState] = useState(false);

    const isBigScreen = useMediaQuery({ query: '(min-width: 675px)' });

    const toggleDrawer = (open: any) => (event: any) => {
        if (
            event.type === "keydown" &&
            (event.key === "Tab" || event.key === "Shift")
        ) {
            return;
        }
        //changes the function state according to the value of open
        setState(open);
    };

    return (
        <Box sx={{ flexGrow: 1 }}>
            <AppBar position="static" sx={{ marginBottom: "20px", backgroundColor: colors.pink[500] }}>
                <Toolbar>
                    <Button
                        to="/"
                        component={Link}
                        color="inherit"
                        sx={{ mr: 2 }}
                        startIcon={<HomeIcon />}>
                    </Button>
                    <Typography variant="h6" component="div" sx={{ mr: 5 }}>
                        Bank Management
                    </Typography>
                    {isBigScreen && <Button
                        to="/bank-management"
                        component={Link}
                        color="inherit"
                        sx={{ mr: 5 }}>
                        Banks
                    </Button>}
                    {isBigScreen && <Button
                        to="/branch-management"
                        component={Link}
                        color="inherit"
                        sx={{ mr: 5 }}>
                        Branches
                    </Button>}
                    {isBigScreen && <Button
                        to="/account-management"
                        component={Link}
                        color="inherit"
                        sx={{ mr: 5 }}>
                        Accounts
                    </Button>}
                    {isBigScreen && <Button
                        to="/customer-management"
                        component={Link}
                        color="inherit"
                        sx={{ mr: 5 }}>
                        Customers
                    </Button>}
                    {!isBigScreen && <IconButton
                        edge="start"
                        color="inherit"
                        aria-label="open drawer"
                        onClick={toggleDrawer(true)}
                        sx={{
                            ml: "auto",
                            display: isBigScreen ? 'none' : 'block',
                        }}>
                        <MenuIcon />
                    </IconButton>}
                    {<Drawer
                        //from which side the drawer slides in
                        anchor="right"
                        //if open is true --> drawer is shown
                        open={open}
                        //function that is called when the drawer should close
                        onClose={toggleDrawer(false)}
                    //function that is called when the drawer should open
                    >
                        {/* The inside of the drawer */}
                        <Box
                            sx={{
                                p: 2,
                                height: 1,
                                backgroundColor: "#ffffff"
                            }}
                        >
                            {/* when clicking the icon it calls the function toggleDrawer and closes the drawer by setting the variable open to false */}
                            <IconButton sx={{ mb: 2 }}>
                                <CloseIcon onClick={toggleDrawer(false)} />
                            </IconButton>

                            <Divider sx={{ mb: 2 }} />

                            <Box sx={{ mb: 2 }}>
                                <ListItemButton to="/bank-management" component={Link}>
                                    <ListItemText primary="Banks" />
                                </ListItemButton>

                                <ListItemButton to="/branch-management" component={Link}>
                                    <ListItemText primary="Branches" />
                                </ListItemButton>

                                <ListItemButton to="/account-management" component={Link}>
                                    <ListItemText primary="Account" />
                                </ListItemButton>

                                <ListItemButton to="/customer-management" component={Link}>
                                    <ListItemText primary="Customers" />
                                </ListItemButton>
                            </Box>
                        </Box>
                    </Drawer>}
                </Toolbar>
            </AppBar>
            <Chat></Chat>
        </Box>
    )
}
