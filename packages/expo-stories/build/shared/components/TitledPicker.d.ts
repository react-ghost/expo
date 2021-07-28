import { TextStyle, ViewStyle } from 'react-native';
declare function TitledPicker({ style, titleStyle, title, value, setValue, items, disabled, }: {
    style?: ViewStyle;
    titleStyle?: TextStyle;
    title?: string;
    value: string;
    items: {
        key: string;
        value: string;
    }[];
    disabled?: boolean;
    setValue: (value: string) => void;
}): JSX.Element;
export { TitledPicker };
