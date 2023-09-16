import { useToast, Button, Box, Heading } from '@chakra-ui/react'
import { CheckIcon } from '@chakra-ui/icons'
import Burning_ship from './blue_ship.jpg';
import './App.css';
import { useMediaQuery } from 'react-responsive';

function App() {
  const toast = useToast()

  const isBigScreen = useMediaQuery({ query: '(min-width: 1080px)' })
  const isTabletOrMobile = useMediaQuery({ query: '(max-width: 1080px)' })
  const isSmall = useMediaQuery({ query: '(max-width: 869px' })

  return (
    <div className="App" style={{ height: 768, width: 1366 }} >
      <header className="App-header">
        <img src={Burning_ship} style={{ transform: 'scale(1) translate(0, 0%)' }} />

        <Box minH={'100%'} style={{ transform: `translate(0px, 565px)`, position: 'absolute' }}>

          {isBigScreen && <Heading as='h3' size={'lg'} noOfLines={4} color={'#fbdb58'} paddingBottom={'10px'} textShadow={'1.5px 1.5px 1.5px red, 0 0 1.5em blue, 0 0 1.5em blue;'}>Arrr, du har trængt ind på mit skib<br></br>det har ramte mig som et sår i mit pirathjerte.<br></br>Du trodser havets kodeks og brød min tillid.<br></br>Må dine skæbnebølger være hårde.</Heading>}
          {isTabletOrMobile && !isSmall && <Heading as='h5' size={'sm'} noOfLines={4} color={'#fbdb58'} paddingBottom={'10px'} textShadow={'1.5px 1.5px 1.5px red, 0 0 1.5em blue, 0 0 1.5em blue;'}>Arrr, du har trængt ind på mit skib<br></br>det har ramte mig som et sår i mit pirathjerte.<br></br>Du trodser havets kodeks og brød min tillid.<br></br>Må dine skæbnebølger være hårde.</Heading>}
          {isSmall && <Heading minW={'100 %'} as='h6' size={'xs'} noOfLines={4} color={'#fbdb58'} paddingBottom={'10px'} textShadow={'1.5px 1.5px 1.5px red, 0 0 1.5em blue, 0 0 1.5em blue;'}>Arrr, du har trængt ind på mit skib<br></br>det har ramte mig som et sår i mit pirathjerte.<br></br>Du trodser havets kodeks og brød min tillid.<br></br>Må dine skæbnebølger være hårde.</Heading>}

          {<Button leftIcon={<CheckIcon />} colorScheme="red" variant="solid"
            onClick={() =>
              toast({
                title: 'Godt gået..! Skriv i terminalen:',
                description: "export blue_ship=1",
                status: 'success',
                duration: 9000,
                isClosable: true,
              })}>
            Sænk Skibet
          </Button>}
        </Box>
      </header>
    </div>
  );
}

export default App;
