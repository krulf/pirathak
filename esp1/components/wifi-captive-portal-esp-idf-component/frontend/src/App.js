import { Text, useToast, Button, Box, InputLeftAddon, InputGroup, Input, Select, SimpleGrid, Heading } from '@chakra-ui/react'
import { CheckIcon } from '@chakra-ui/icons'
import Burning_ship from './Burning_ship.jpg';
import './App.css';
import { useState, useRef } from 'react';

function App() {
  const [show, setShow] = useState(true)
  const handleClick = () => setShow(!show)

  const toast = useToast()

  return (
    <div className="App">
      <header className="App-header">
        <img src={Burning_ship} maxW={'75%'} maxH={'75%'} style={{ transform: 'scale(1) translate(0, -8%)' }} />

        <Box minH={'100%'} style={{ transform: `translate(0px, 825px)`, position: 'absolute' }}>
          <Heading as='h3' size={'lg'} color={'#fbdb58'} noOfLines={4} paddingBottom={'10px'} textShadow={'1.5px 1.5px 1.5px red, 0 0 1.5em blue, 0 0 1.5em blue;'}>Arrr, du har trængt ind på mit skib<br></br>det har ramte mig som et sår i mit pirathjerte.<br></br>Du trodser havets kodeks og brød min tillid.<br></br>Må dine skæbnebølger være hårde.</Heading>

          {/*<Button leftIcon={<CheckIcon />} colorScheme="green" variant="solid"
            onClick={() =>
              toast({
                title: 'System Activated...!',
                description: "The settings is saved",
                status: 'success',
                duration: 9000,
                isClosable: true,
              })}>
            Activate
          </Button>*/}
        </Box>
      </header>
    </div>
  );
}

export default App;
