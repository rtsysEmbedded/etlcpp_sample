
#include <UnitTest++/UnitTest++.h>
#include "../packet_buffer.hpp" // Make sure this includes your class
#include "etl/queue.h" // If needed for other dependencies

// Test case 1: Test buffer append and extract
TEST(AppendAndExtract)
{
    packet_buffer buffer;

    // Create a sample packet
    Packet p;
    p.size = 10;
    for (int i = 0; i < p.size; ++i) {
        p.data[i] = static_cast<uint8_t>(i);
    }

    // Check initial empty status
    CHECK_EQUAL(buffer.is_empty(), buffer_status::BUFFER_EMPTY);

    // Append the packet to the buffer
    CHECK_EQUAL(buffer.append(p), buffer_status::BUFFER_OK);

    // Check that the buffer is no longer empty
    CHECK_EQUAL(buffer.is_empty(), buffer_status::BUFFER_OK);

    // Extract the packet from the buffer
    Packet extractedPacket;
    CHECK_EQUAL(buffer.extract(&extractedPacket), buffer_status::BUFFER_OK);

    // Verify that the extracted packet has the same data as the original one
    CHECK_EQUAL(extractedPacket.size, p.size);
    for (int i = 0; i < p.size; ++i) {
        CHECK_EQUAL(extractedPacket.data[i], p.data[i]);
    }

    // Verify that the buffer is now empty again
    CHECK_EQUAL(buffer.is_empty(), buffer_status::BUFFER_EMPTY);
}

// Test case 2: Test buffer full scenario
TEST(BufferFull)
{
    packet_buffer buffer;

    // Create a sample packet
    Packet p;
    p.size = 10;
    for (int i = 0; i < p.size; ++i) {
        p.data[i] = static_cast<uint8_t>(i);
    }

    // Append 16 packets to the buffer (buffer size limit is 16)
    for (int i = 0; i < 16; ++i) {
        CHECK_EQUAL(buffer.append(p), buffer_status::BUFFER_OK);
    }

    // Try appending one more packet beyond the buffer capacity
    CHECK_EQUAL(buffer.append(p), buffer_status::BUFFER_FULL);
}

// Test case 3: Test buffer empty status
TEST(BufferEmptyStatus)
{
    packet_buffer buffer;

    // Check initial empty status
    CHECK_EQUAL(buffer.is_empty(), buffer_status::BUFFER_EMPTY);

    // Create a sample packet and append it to the buffer
    Packet p;
    p.size = 10;
    for (int i = 0; i < p.size; ++i) {
        p.data[i] = static_cast<uint8_t>(i);
    }
    CHECK_EQUAL(buffer.append(p), buffer_status::BUFFER_OK);

    // Check that the buffer is no longer empty
    CHECK_EQUAL(buffer.is_empty(), buffer_status::BUFFER_OK);

    // Extract the packet and check if buffer is empty again
    Packet extractedPacket;
    CHECK_EQUAL(buffer.extract(&extractedPacket), buffer_status::BUFFER_OK);
    CHECK_EQUAL(buffer.is_empty(), buffer_status::BUFFER_EMPTY);
}

// Test case 4: Test extraction from an empty buffer
TEST(ExtractFromEmptyBuffer)
{
    packet_buffer buffer;

    // Try extracting from an empty buffer
    Packet extractedPacket;
    CHECK_EQUAL(buffer.extract(&extractedPacket), buffer_status::BUFFER_EMPTY);
}


int main()
{
  return UnitTest::RunAllTests();
}