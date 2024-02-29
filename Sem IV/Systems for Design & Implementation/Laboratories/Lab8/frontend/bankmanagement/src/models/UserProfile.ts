export interface UserProfile {
    id?: number;
    first_name: string;
    last_name: string;
    bio: string;
    location: string;
    gender: string;
    user?: number;
    entities_added?: number[];
}